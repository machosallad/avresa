#include "application.h"
#include "config.h"
#include "train_announcement_string_builder.h"

Application::Application() : m_trafikverketClient(SERVER_KEY, SERVER_URL, STATION_CODE), m_wifiManager(WIFI_SSID, WIFI_PASSWORD)
{
    // Constructor
}

Application::~Application()
{
    // Destructor
}

void Application::init(uint8_t uuid)
{
    // Fire up the system by connecting to WiFi, coniguring the Web server and fetching the latest announcements
    m_display.init(uuid);
    showSplashScreen();
    m_display.printTextCentered("Connecting");
    m_wifiManager.connectToWifi();
    m_webServer.init();
    m_webServer.registerObserver(Setting::Brightness, std::bind(&Display::setBrightness, &m_display, std::placeholders::_1));
    m_webServer.registerObserver(Setting::StationCode, std::bind(&TrafikverketClient::setStationCode, &m_trafikverketClient, std::placeholders::_1));
    m_webServer.registerReloadObserver(std::bind(&Application::loadTrainStationAnnouncements, this));
    m_display.printTextCentered("Updating");

    if (getLatestAnnouncements())
    {
        updateDisplayInformation();
    }
    else
    {
        m_display.printTextCentered("Failed to update!");
    }
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
    if (response.length() == 0)
        return false;

    m_announcements.updateAnnouncements(response);
    return true;
}

void Application::updateDisplayInformation()
{
    if (m_announcements.getNumAnnouncements() == 0)
    {
        m_display.printTextCentered("No departures");
    }

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

        m_display.printText(train, 0, i * m_display.getFontHeight());
        m_display.printTextRightAligned(information, m_display.getDisplayWidth(), i * m_display.getFontHeight());
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
        m_display.printTextCentered("Error: " + m_trafikverketClient.getLastResponseCode());
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
    unsigned long currentTime = millis();
    if (currentTime - lastRequestTime >= nextRequestInterval)
    {
        lastRequestTime = currentTime;
        loadTrainStationAnnouncements();
        nextRequestInterval = getRequestInterval();
    }

    if (!m_wifiManager.isConnected())
    {
        m_display.printTextCentered("WiFi disconnected!");
    }
}

void Application::showSplashScreen()
{
    m_display.clearScreen();
    m_display.printTextCentered("MakerMelin", Display::Color::GREEN);
    delay(2000);
    m_display.clearScreen();
}