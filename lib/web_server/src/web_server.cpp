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
      "/setting", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [this](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
      { handleSettingUpdate(request, data, len, index, total); });

  m_server.on(
      "/configuration", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [this](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
      { handleConfigurationUpdate(request, data, len, index, total); });

  m_server.on(
      "/reload", HTTP_GET, [this](AsyncWebServerRequest *request)
      { handleReloadRequest(); 
        request->send(200, "text/plain", "OK"); });

  // Start the server
  m_server.begin();
}

void WebServer::handleSettingUpdate(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, (const char *)data);

  // Check if the doc conains a value field
  if (!doc.containsKey("setting") || !doc.containsKey("value"))
  {
    request->send(400, "application/json", "{\"message\":\"Invalid request\"}");
    return;
  }

  String setting = doc["setting"].as<String>();
  if (setting == "color")
  {
    handleRequest(Setting::Color, doc["value"].as<String>());
  }
  else if (setting == "brightness")
  {
    handleRequest(Setting::Brightness, doc["value"].as<uint8_t>());
  }
  else if (setting == "stationCode")
  {
    handleRequest(Setting::StationCode, doc["value"].as<String>());
  }
  else
  {
    request->send(400, "application/json", "{\"message\":\"Unknown setting\"}");
    return;
  }

  request->send(200, "application/json", "{\"message\":\"Setting updated successfully\"}");
}

void WebServer::handleConfigurationUpdate(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, (const char *)data);

  if (error)
  {
    request->send(400, "application/json", "{\"message\":\"Invalid JSON\"}");
    return;
  }

  bool updated = false;

  if (doc.containsKey("ssid") && doc.containsKey("password"))
  {
    handleRequest(Setting::WifiSSID, doc["ssid"].as<String>());
    handleRequest(Setting::WifiPassword, doc["password"].as<String>());
    updated = true;
  }

  if (doc.containsKey("apiKey"))
  {
    handleRequest(Setting::ApiKey, doc["apiKey"].as<String>());
    updated = true;
  }

  if (updated)
  {
    request->send(200, "application/json", "{\"message\":\"Configuration updated successfully\"}");
  }
  else
  {
    request->send(400, "application/json", "{\"message\":\"Invalid request\"}");
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
