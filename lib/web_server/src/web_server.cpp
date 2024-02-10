#include "web_server.h"

WebServer::WebServer() : m_server(80)
{
    // Constructor implementation
}

WebServer::~WebServer()
{
    // Destructor implementation
}

void WebServer::init()
{
    // Serve the HTML page
    m_server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                {
                String html = "<html><body>";
                html += "<input type='range' min='10' max='100' id='brightness' onchange='updateBrightness(this.value)' />";
                html += "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js'></script>";
                html += "<script>function updateBrightness(value) { $.get('/brightness?level=' + value); }</script>";
                html += "</body></html>";
            request->send(200, "text/html", html); });

    // Handle brightness level updates
    m_server.on("/brightness", HTTP_GET, [this](AsyncWebServerRequest *request)
                {
                if (request->hasParam("level")) {
                    String level = request->getParam("level")->value();
                    uint8_t brightness = level.toInt();
                    handleRequest(Setting::Brightness, brightness);
                }
            request->send(200, "text/plain", "OK"); });

    // Start the server
    m_server.begin();
}

void WebServer::registerObserver(Setting setting, CallbackInt observer)
{
    m_observersInt[setting].push_back(observer);
}

void WebServer::registerObserver(Setting setting, CallbackString observer)
{
    m_observersString[setting].push_back(observer);
}

void WebServer::handleRequest(Setting setting, uint8_t value)
{
    for (auto &observer : m_observersInt[setting])
    {
        observer(value);
    }
}

void WebServer::handleRequest(Setting setting, const String &value)
{
    for (auto &observer : m_observersString[setting])
    {
        observer(value.c_str());
    }
}