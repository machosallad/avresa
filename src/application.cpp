#include "application.h"
#include "train_announcement_string_builder.h"

Application::Application(const Secrets &secret, const Parameter &parameter, FileManager &fileManager)
    : m_secrets(secret),
      m_parameters(parameter),
      m_trafikverketClient(secret.apiKey, parameter.stationCode),
      m_wifiManager(secret.ssid, secret.password),
      m_display(parameter.brightness),
      m_announcements(parameter.stationCode),
      m_fileManager(fileManager),
      m_otaManager(Version::semver(), m_display)
{
    // Initialization code
}

Application::~Application()
{
    // Destructor
}

void Application::init(uint8_t displayType)
{
    // Fire up the system by connecting to WiFi, coniguring the Web server and fetching the latest announcements
    m_display.init(displayType);
    showSplashScreen();

    // Register observers for settings and configuration
    m_webServer.registerObserver(Setting::Brightness, std::bind(&Display::setBrightness, &m_display, std::placeholders::_1));
    m_webServer.registerObserver(Setting::StationCode, std::bind(&TrafikverketClient::setStationCode, &m_trafikverketClient, std::placeholders::_1));
    m_webServer.registerObserver(Setting::StationCode, std::bind(&FileManager::saveStationCode, &m_fileManager, std::placeholders::_1));
    m_webServer.registerReloadObserver(std::bind(&Application::loadTrainStationAnnouncements, this));
    m_webServer.registerObserver(Setting::ApiKey, std::bind(&TrafikverketClient::setApiKey, &m_trafikverketClient, std::placeholders::_1));
    m_webServer.registerObserver(Setting::WifiSSID, std::bind(&WiFiManager::setSSID, &m_wifiManager, std::placeholders::_1));
    m_webServer.registerObserver(Setting::WifiPassword, std::bind(&WiFiManager::setPassword, &m_wifiManager, std::placeholders::_1));
    m_webServer.registerObserver(Setting::WifiSSID, std::bind(&FileManager::saveWifiSSID, &m_fileManager, std::placeholders::_1));
    m_webServer.registerObserver(Setting::WifiPassword, std::bind(&FileManager::saveWifiPassword, &m_fileManager, std::placeholders::_1));
    m_webServer.registerObserver(Setting::ApiKey, std::bind(&FileManager::saveApiKey, &m_fileManager, std::placeholders::_1));

    m_display.printText("Connect to WiFi", Display::Line::Line1);
    if (m_wifiManager.connectToWifi())
    {
        m_display.printText("Connect to WiFi", Display::Line::Line1, Display::Color::Green);
        m_display.printText(m_wifiManager.getIpAddress(), Display::Line::Line2, Display::Color::Green);
        m_display.printText("Checking for updates", Display::Line::Line3);

        if (!Version::localBuild())
        {
            if (m_otaManager.updateAvailable())
            {
                if (m_otaManager.updateFirmware())
                {
                    m_display.printTextCentered("Update successful", Display::Color::Green);
                    delay(2000);
                    m_display.clearScreen();
                    ESP.restart();
                }
                else
                {
                    m_display.printTextCentered("Update failed", Display::Color::Red);
                    delay(2000);
                }
            }
        }

        m_display.printText("Checking for updates", Display::Line::Line3, Display::Color::Green);
        m_display.printText("Update departures", Display::Line::Line4, Display::Color::Orange);

        if (getLatestAnnouncements())
        {
            m_display.printText("Update departures", Display::Line::Line4, Display::Color::Green);
            delay(1000);
            updateDisplayInformation();
        }
        else
        {
            m_display.printTextCentered("Failed to update!");
        }
    }
    else
    {
        Serial.println("Failed to connect to WiFi, start captive portal");
        String wifiString = "WIFI:S:" + m_wifiManager.getAPName() + ";T:nopass;;";
        m_display.printText("Connect to AVRESA", Display::Line::Line1, Display::Color::Orange, true, 3, 2);
        m_display.printText("with your phone to", Display::Line::Line2, Display::Color::Orange, false, 3, 2);
        m_display.printText("setup this device.", Display::Line::Line3, Display::Color::Orange, false, 3, 2);
        m_display.drawQrCode(wifiString, m_display.getDisplayWidth() - 31, 2, Display::Color::White);
        m_wifiManager.startCaptivePortal();
        m_webServer.useCaptivePortal(true);
    }

    m_webServer.init();
}

bool Application::loadStationNames()
{
    bool status = false;
    if (m_wifiManager.isConnected())
    {
        String response = m_trafikverketClient.getTrainStations();
        Serial.println("Successfully loaded station names");
        m_announcements.updateStationNames(response);
        status = true;
    }
    else
    {
        Serial.println("WiFi Disconnected");
        status = false;
    }
    return status;
}

bool Application::getLatestAnnouncements()
{
    String response = m_trafikverketClient.getTrainAnnouncements();
    if (response.length() == 0 || m_trafikverketClient.getLastResponseCode() != 200)
        return false;

    m_announcements.updateAnnouncements(response);
    return true;
}

void Application::updateDisplayInformation()
{
    for (int i = 0; i < m_announcements.getNumAnnouncements(); ++i)
    {
        TrainAnnouncement announcement = m_announcements.getAnnouncement(i);
        TrainAnnouncementStringBuilder announcementBuilder;
        TrainAnnouncementStringBuilder informationBuilder;
        String train = announcementBuilder
                           .addTime(announcement.getAdvertisedTime())
                           .addSpace()
                           .addStationName(StationLookup::getInstance().getStationName(announcement.getToLocation()))
                           .build();

        String information = informationBuilder
                                 .addEstimatedTime(announcement.getEstimatedTime(), announcement.isDelayed())
                                 .addSpace(announcement.isDelayed() && announcement.isCanceled())
                                 .addCanceled(announcement.isCanceled(), announcement.getDeviationCode())
                                 .build();

        // Clear the display before the first announcement is printed
        if (i == 0)
            m_display.clearScreen();

        m_display.printText(train, i);
        m_display.printTextRightAligned(information, i);
    }
}

void Application::loadTrainStationAnnouncements()
{
    if (getLatestAnnouncements())
    {
        updateDisplayInformation();
        fetchErrorOccured = false;
    }
    else
    {
        fetchErrorOccured = true;
    }
}

unsigned long Application::getRequestInterval()
{
    // If an error occurred, request data more frequently using backoff strategy
    if (fetchErrorOccured)
    {
        // Increase the request interval exponentially
        errorRequestInterval *= 2;
        if (errorRequestInterval > requestInterval)
        {
            errorRequestInterval = requestInterval;
        }
        return errorRequestInterval;
    }
    else
    {
        // Reset the request interval to the initial value
        errorRequestInterval = 1000;
        return requestInterval;
    }
}

void Application::run()
{
    // Update the current state based on the current conditions
    if (m_webServer.isCaptivePortal())
    {
        m_state = State::CaptivePortal;
    }
    else if (!m_wifiManager.isConnected())
    {
        m_state = State::Error;
    }
    else
    {
        m_state = State::NormalOperation;
    }

    switch (m_state)
    {
    case State::CaptivePortal:
        m_wifiManager.processDNSRequests();
        break;

    case State::NormalOperation:
    {
        unsigned long currentTime = millis();
        if (currentTime - lastRequestTime >= nextRequestInterval)
        {
            lastRequestTime = currentTime;
            loadTrainStationAnnouncements();
            nextRequestInterval = getRequestInterval();
        }
        break;
    }
    default:
        break;
    }
}

void Application::showSplashScreen()
{
    m_display.clearScreen();
    m_display.fadeInTextCentered("Avgång by MakerMelin", Display::Color::Green);
    delay(1000);
    m_display.fadeInTextCentered(Version::semver(), Display::Color::Green);
    delay(1000);
    if (Version::localBuild())
    {
        m_display.fadeInTextCentered("Local build", Display::Color::Blue);
        delay(500);
    }
    m_display.clearScreen();
}