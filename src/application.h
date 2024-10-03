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
#include "eeprom_manager.h"
#include "file_manager.h"
#include "ota_manager.h"

class Application
{
public:
    Application(const Secrets &secret, const Parameter &parameter, FileManager &fileManager);
    ~Application();
    void init(uint8_t displayType);
    unsigned long getRequestInterval();
    void run();
    void showSplashScreen();

private:
    enum class State
    {
        CaptivePortal,
        NormalOperation,
        Error
    };
    State m_state = State::NormalOperation;
    bool loadStationNames();
    bool getLatestAnnouncements();
    void updateDisplayInformation();
    void loadTrainStationAnnouncements();
    unsigned long lastRequestTime = 0;            // When the last request was made
    const unsigned long requestInterval = 300000; // Request interval (5 minutes)
    unsigned long errorRequestInterval = 1000;
    unsigned long nextRequestInterval = requestInterval;
    bool fetchErrorOccured = false;
    TrafikverketClient m_trafikverketClient;
    ContentManager m_contentManager;
    WiFiManager m_wifiManager;
    Display m_display;
    TrainStationAnnouncements m_announcements;
    WebServer m_webServer;
    Secrets m_secrets;
    Parameter m_parameters;
    FileManager &m_fileManager;
    OtaManager m_otaManager;
};

#endif // APPLICATION_H