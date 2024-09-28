#include "web_server.h"
#ifdef __has_include
#if __has_include("index_html.h")
#include "index_html.h"
#else
// Provide a fallback or a dummy definition if the file is not found
const char index_html[] PROGMEM = "";
#endif
#else
// Fallback for compilers that do not support __has_include
#include "index_html.h"
#endif

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
      "/configuration/saveWifi", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [this](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
      { handleSaveWifiSettings(request, data, len, index, total); });

  m_server.on(
      "/configuration/saveApiKey", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [this](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
      { handleSaveApiKey(request, data, len, index, total); });

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

void WebServer::handleSaveWifiSettings(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, (const char *)data);

  if (doc.containsKey("ssid") && doc.containsKey("password"))
  {
    String ssid = doc["ssid"].as<String>();
    String password = doc["password"].as<String>();

    // Save the WiFi credentials
    handleRequest(Setting::WifiSSID, ssid);
    handleRequest(Setting::WifiPassword, password);

    request->send(200, "application/json", "{\"message\":\"WiFi settings saved. Please restart the device.\"}");
  }
  else
  {
    request->send(400, "application/json", "{\"message\":\"Missing parameters\"}");
  }
}

void WebServer::handleSaveApiKey(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, (const char *)data);

  if (doc.containsKey("apiKey"))
  {
    String apiKey = doc["apiKey"].as<String>();

    // Save the API key
    handleRequest(Setting::ApiKey, apiKey);

    request->send(200, "application/json", "{\"message\":\"API key saved. Please restart the device.\"}");
  }
  else
  {
    request->send(400, "application/json", "{\"message\":\"Missing parameters\"}");
  }
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
  Serial.println("Handling request");
  Serial.print("Setting: ");
  Serial.println(static_cast<int>(setting));
  Serial.print("Value: ");
  Serial.println(value);
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
