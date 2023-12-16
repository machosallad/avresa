#include <HTTPClient.h>
#include "trafikverket_client.h"
#include "xml_requests.h"

TrafikverketClient::TrafikverketClient(const String &authKey, const String &serverUrl)
    : m_authKey(authKey), m_serverUrl(serverUrl)
{
    // Constructor implementation
}

TrafikverketClient::~TrafikverketClient()
{
    // Destructor implementation
}

String TrafikverketClient::getTrainAnnouncements(const String &stationCode)
{

    HTTPClient http; // Declare an object of class TrafikverketClient
    String response = "";
    http.begin(m_serverUrl);
    http.addHeader("Content-Type", "text/xml");
    // Add data to the request body
    String body = TRAIN_ANNOUNCEMENT_REQUEST(m_authKey, stationCode);

    int httpResponseCode = http.POST(body);
    if (httpResponseCode > 0)
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