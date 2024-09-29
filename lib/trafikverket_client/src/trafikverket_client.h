#ifndef TRAFIKVERKET_CLIENT_H
#define TRAFIKVERKET_CLIENT_H
#include <Arduino.h>

class TrafikverketClient
{
public:
    TrafikverketClient(const String &serverKey, const String &stationCode);
    ~TrafikverketClient();

    String getTrainAnnouncements(const String &stationCode);
    String getTrainAnnouncements();
    int getLastResponseCode();
    void setStationCode(const String &stationCode);
    String getTrainStations();
    void setApiKey(const String &apiKey);

private:
    String sendHttpRequest(const String &serverUrl, const String &body);
    String m_authKey;
    static const String m_serverUrl;
    String m_stationCode;
    int m_lastResponseCode = 0;
};

#endif // TRAFIKVERKET_CLIENT_H