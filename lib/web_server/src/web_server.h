#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "ESPAsyncWebServer.h"
#include "settings.h"
#include <map>

class WebServer
{
public:
    using CallbackInt = std::function<void(uint8_t)>;
    using CallbackString = std::function<void(std::string)>;

    WebServer();
    ~WebServer();
    void init();

    void registerObserver(Setting setting, CallbackInt observer);
    void registerObserver(Setting setting, CallbackString observer);

private:
    void handleRequest(Setting setting, uint8_t value);
    void handleRequest(Setting setting, const String &value);

    AsyncWebServer m_server;
    std::map<Setting, std::vector<CallbackInt>> m_observersInt;
    std::map<Setting, std::vector<CallbackString>> m_observersString;
};

#endif // WEB_SERVER_H