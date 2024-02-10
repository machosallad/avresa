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
                    String html;
                    html += "<!DOCTYPE html>\n";
                    html += "<html>\n";
                    html += "<head>\n";
                    html += "    <title>Avresa</title>\n";
                    html += "    <script>\n";
                    html += "        function updateSetting(setting, value) {\n";
                    html += "            var xhr = new XMLHttpRequest();\n";
                    html += "            xhr.open(\"POST\", \"/setting/\" + setting, true);\n";
                    html += "            xhr.setRequestHeader('Content-Type', 'application/json');\n";
                    html += "            xhr.send(JSON.stringify({ value: value }));\n";
                    html += "        }\n";
                    html += "    </script>\n";
                    html += "</head>\n";
                    html += "<body>\n";
                    html += "    <h1>Avresa</h1>\n";
                    html += "    <h2>Brightness</h2>\n";
                    html += "    <input type=\"range\" min=\"0\" max=\"100\" value=\"50\" class=\"slider\" id=\"brightness\" onchange=\"updateSetting('brightness', Number(this.value))\">\n";
                    html += "    <h2>Color</h2>\n";
                    html += "    <select id=\"color\" onchange=\"updateSetting('color', this.value)\">\n";
                    html += "        <option value=\"yellow\">Yellow</option>\n";
                    html += "        <option value=\"red\">Red</option>\n";
                    html += "        <option value=\"green\">Green</option>\n";
                    html += "    </select>\n";
                    html += "    <h2>Station</h2>\n";
                    html += "    <select id=\"stationCode\" onchange=\"updateSetting('stationCode', this.value)\">\n";
                    html += "        <option value=\"Sl\">Sala</option>\n";
                    html += "        <option value=\"U\">Uppsala</option>\n";
                    html += "        <option value=\"Vå\">Västerås</option>\n";
                    html += "        <option value=\"Cst\">Stockholm C</option>\n";
                    html += "    </select>\n";
                    html += "</body>\n";
                    html += "</html>\n";
            request->send(200, "text/html", html); });

    m_server.onNotFound([this](AsyncWebServerRequest *request)
                        { notFound(request); });

    m_server.on(
        "/setting/color", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [this](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        { handleSettingUpdate(request, data, len, index, total, Setting::Color); });

    m_server.on(
        "/setting/stationCode", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [this](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        { handleSettingUpdate(request, data, len, index, total, Setting::StationCode); });

    m_server.on(
        "/setting/brightness", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [this](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        { handleSettingUpdate(request, data, len, index, total, Setting::Brightness); });

    // Start the server
    m_server.begin();
}

void WebServer::handleSettingUpdate(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total, Setting setting)
{
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, (const char *)data);

    // Check if the doc conains a value field
    if (!doc.containsKey("value"))
    {
        request->send(400, "application/json", "{\"message\":\"Invalid request\"}");
        return;
    }

    if (doc["value"].is<int>())
    {
        handleRequest(setting, doc["value"].as<int>());
    }
    else if (doc["value"].is<String>())
    {
        handleRequest(setting, doc["value"].as<String>());
    }
    else
    {
        request->send(400, "application/json", "{\"message\":\"Invalid request\"}");
        return;
    }

    request->send(200, "text/plain", "OK");
}

void WebServer::notFound(AsyncWebServerRequest *request)
{
    request->send(404, "application/json", "{\"message\":\"Not found\"}");
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