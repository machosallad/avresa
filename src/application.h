#ifndef APPLICATION_H
#define APPLICATION_H

#include "trafikverket_client.h"
#include "content_manager.h"
#include "web_server.h"
#include "wifi_manager.h"
#include "train_station_announcements.h"
#include "display.h"
#include "settings.h"
#include "station_lockup.h"

class Application
{
public:
    Application();
    ~Application();
    void init();
    void run();
    void showSplashScreen();

private:
    bool loadStationNames();
    bool getLatestAnnouncements();
    void updateDisplayInformation();
    void loadTrainStationAnnouncements();
    unsigned long lastRequestTime = 0;            // When the last request was made
    const unsigned long requestInterval = 300000; // Request interval (5 minutes)
    TrafikverketClient m_trafikverketClient;
    ContentManager m_contentManager;
    WiFiManager m_wifiManager;
    Display m_display;
    TrainStationAnnouncements m_announcements;
    WebServer m_webServer;
};

#endif // APPLICATION_H