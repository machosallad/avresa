#include "application.h"
#include "config.h"
#include "train_announcement_string_builder.h"

Application::Application() : m_trafikverketClient(SERVER_KEY, SERVER_URL), m_wifiManager(WIFI_SSID, WIFI_PASSWORD)
{
    // Constructor
}

Application::~Application()
{
    // Destructor
}

void Application::init()
{
    m_display.printTextCentered("Connecting");
    m_wifiManager.connectToWifi();
    m_display.clearScreen();
    m_display.printTextCentered("Updating");
    if (getLatestAnnouncements())
    {
        updateDisplay();
    }
}

bool Application::getLatestAnnouncements()
{
    bool status = false;
    if (m_wifiManager.isConnected())
    {
        String response = m_trafikverketClient.getTrainAnnouncements(STATION_CODE);
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

void Application::updateDisplay()
{
    m_display.clearScreen();
    for (int i = 0; i < m_announcements.getNumAnnouncements(); ++i)
    {
        TrainAnnouncement announcement = m_announcements.getAnnouncement(i);
        TrainAnnouncementStringBuilder builder;
        String text = builder.addTime(announcement.getAdvertisedTimeAtLocation())
                          .addSpace()
                          .addStationName(TrainAnnouncement::getStationName(announcement.getToLocation()))
                          .build();

        m_display.printText(text, 0, i * 8);
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
            updateDisplay();
        }
    }
}