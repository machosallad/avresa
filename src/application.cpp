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

void Application::init()
{
    // Fire up the system by connecting to WiFi, coniguring the Web server and fetching the latest announcements
    showSplashScreen();
    m_display.printTextCentered("Connecting");
    m_wifiManager.connectToWifi();
    m_webServer.init();
    m_webServer.registerObserver(Setting::Brightness, std::bind(&Display::setBrightness, &m_display, std::placeholders::_1));
    m_webServer.registerObserver(Setting::StationCode, std::bind(&TrafikverketClient::setStationCode, &m_trafikverketClient, std::placeholders::_1));
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

bool Application::getLatestAnnouncements()
{
    bool status = false;
    if (m_wifiManager.isConnected())
    {
        String response = m_trafikverketClient.getTrainAnnouncements();
        m_announcements.updateAnnouncements(response);
        status = true;
    }
    else
    {
        Serial.println("WiFi Disconnected");
        status = false;
    }
    return status;
}

void Application::updateDisplayInformation()
{
    m_display.clearScreen();
    for (int i = 0; i < m_announcements.getNumAnnouncements(); ++i)
    {
        TrainAnnouncement announcement = m_announcements.getAnnouncement(i);
        TrainAnnouncementStringBuilder announcementBuilder;
        TrainAnnouncementStringBuilder informationBuilder;
        String train = announcementBuilder
                           .addTime(announcement.getAdvertisedTime())
                           .addSpace()
                           .addStationName(TrainAnnouncement::getStationName(announcement.getToLocation()))
                           .build();

        String information = informationBuilder
                                 .addEstimatedTime(announcement.getEstimatedTime(), announcement.isDelayed())
                                 .addSpace(announcement.isDelayed() && announcement.isCanceled())
                                 .addCanceled(announcement.isCanceled(), announcement.getDeviationCode())
                                 .build();

        m_display.printText(train, 0, i * m_display.getFontHeight());
        m_display.printTextRightAligned(information, m_display.getDisplayWidth(), i * m_display.getFontHeight());
    }
}

void Application::run()
{
    unsigned long currentTime = millis();
    if (currentTime - lastRequestTime >= requestInterval)
    {
        lastRequestTime = currentTime;
        if (getLatestAnnouncements())
        {
            updateDisplayInformation();
        }
        else
        {
            m_display.printTextCentered("Failed to update!");
        }
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