#include "web_server.h"

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css">
    <title>Avresa</title>
    <script>
        function updateSetting(setting, value) {
            var xhr = new XMLHttpRequest();
            xhr.open("POST", "/setting/" + setting, true);
            xhr.setRequestHeader('Content-Type', 'application/json');
            xhr.send(JSON.stringify({ value: value }));
        }
        function reloadAnnouncements() {
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/reload", true);
            xhr.send();
        }
    </script>
</head>
<body class="bg-dark text-white">
    <div class="container">
        <h1 class="mt-4">Avresa</h1>
        <div class="my-4">
            <h2>Brightness</h2>
            <input type="range" min="0" max="100" value="50" class="custom-range" id="brightness" onchange="updateSetting('brightness', Number(this.value))">
        </div>
        <div class="my-4">
            <h2>Color</h2>
            <select class="custom-select bg-secondary text-white" id="color" onchange="updateSetting('color', this.value)">
                <option value="yellow">Yellow</option>
                <option value="red">Red</option>
                <option value="green">Green</option>
            </select>
        </div>
        <div class="my-4">
            <h2>Station</h2>
            <select class="custom-select bg-secondary text-white" id="stationCode" onchange="updateSetting('stationCode', this.value)">
                <option value="Sl">Sala</option>
                <option value="U">Uppsala</option>
                <option value="Vå">Västerås</option>
                <option value="Cst">Stockholm C</option>
            </select>
        </div>
        <div class="my-4">
            <h2>Announcements</h2>
            <button class="btn btn-light" onclick="reloadAnnouncements()">Reload</button>
        </div>
    </div>
</body>
</html>
)rawliteral";

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
                { request->send(200, "text/html", FPSTR(index_html)); });

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

    m_server.on(
        "/reload", HTTP_GET, [this](AsyncWebServerRequest *request)
        { handleReloadRequest(); 
        request->send(200, "text/plain", "OK"); });

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

void WebServer::registerReloadObserver(CallbackVoid observer)
{
    m_reloadObservers.push_back(observer);
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

void WebServer::handleReloadRequest()
{
    for (auto &observer : m_reloadObservers)
    {
        observer();
    }
}
