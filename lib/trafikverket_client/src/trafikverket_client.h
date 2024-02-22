#ifndef TRAFIKVERKET_CLIENT_H
#define TRAFIKVERKET_CLIENT_H
#include <Arduino.h>

class TrafikverketClient
{
public:
    TrafikverketClient(const String &serverKey, const String &serverUrl, const String &stationCode);
    ~TrafikverketClient();

    String getTrainAnnouncements(const String &stationCode);
    String getTrainAnnouncements();
    void setStationCode(const String &stationCode);
    String getTrainStations();

private:
    String m_authKey;
    String m_serverUrl;
    String m_stationCode;
};

#endif // TRAFIKVERKET_CLIENT_H