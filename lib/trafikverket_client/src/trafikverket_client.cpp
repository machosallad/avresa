#include <HTTPClient.h>
#include "trafikverket_client.h"
#include "xml_requests.h"

TrafikverketClient::TrafikverketClient(const String &authKey, const String &serverUrl, const String &stationCode)
    : m_authKey(authKey), m_serverUrl(serverUrl), m_stationCode(stationCode), m_lastResponseCode(0)
{
    // Constructor implementation
}

TrafikverketClient::~TrafikverketClient()
{
    // Destructor implementation
}

String TrafikverketClient::getTrainAnnouncements(const String &stationCode)
{
    String body = TRAIN_ANNOUNCEMENT_REQUEST(m_authKey, stationCode);
    return sendHttpRequest(m_serverUrl, body);
}

String TrafikverketClient::getTrainAnnouncements()
{
    return getTrainAnnouncements(m_stationCode);
}

int TrafikverketClient::getLastResponseCode()
{
    return m_lastResponseCode;
}

void TrafikverketClient::setStationCode(const String &stationCode)
{
    m_stationCode = stationCode;
}

String TrafikverketClient::getTrainStations()
{
    String body = TRAIN_STATIONS_REQUEST(m_authKey);
    return sendHttpRequest(m_serverUrl, body);
}

String TrafikverketClient::sendHttpRequest(const String &serverUrl, const String &body)
{
    HTTPClient http;
    String response = "";
    http.begin(serverUrl);
    http.addHeader("Content-Type", "text/xml");

    int httpResponseCode = http.POST(body);
    m_lastResponseCode = httpResponseCode;

    if (httpResponseCode == 200)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        response = http.getString();
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    http.end();

    return response;
}

// Implement your methods here