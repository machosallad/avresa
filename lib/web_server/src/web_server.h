#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "ESPAsyncWebServer.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "settings.h"
#include <map>

class WebServer
{
public:
    using CallbackInt = std::function<void(uint8_t)>;
    using CallbackString = std::function<void(String)>;
    using CallbackVoid = std::function<void()>;

    WebServer();
    ~WebServer();
    void init();

    void registerObserver(Setting setting, CallbackInt observer);
    void registerObserver(Setting setting, CallbackString observer);
    void registerReloadObserver(CallbackVoid observer);

private:
    void handleRequest(Setting setting, uint8_t value);
    void handleRequest(Setting setting, const String &value);
    void handleReloadRequest();
    void handleSettingUpdate(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
    void handleConfigurationUpdate(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
    void notFound(AsyncWebServerRequest *request);

    AsyncWebServer m_server;
    std::map<Setting, std::vector<CallbackInt>> m_observersInt;
    std::map<Setting, std::vector<CallbackString>> m_observersString;
    std::vector<CallbackVoid> m_reloadObservers;
};

#endif // WEB_SERVER_H