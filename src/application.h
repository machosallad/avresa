#ifndef APPLICATION_H
#define APPLICATION_H

#include "trafikverket_client.h"
#include "content_manager.h"
#include "web_server.h"
#include "wifi_manager.h"
#include "announcements.h"
#include "display.h"

class Application
{
public:
    Application();
    ~Application();
    void init();
    void run();

private:
    bool getLatestAnnouncements();
    void updateDisplay();
    unsigned long lastRequestTime = 0;            // When the last request was made
    const unsigned long requestInterval = 300000; // Request interval (5 minutes)
    TrafikverketClient m_trafikverketClient;
    ContentManager m_contentManager;
    WiFiManager m_wifiManager;
    Display m_display;
    Announcements m_announcements;
};

#endif // APPLICATION_H