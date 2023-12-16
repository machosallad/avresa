#ifndef TRAFIKVERKET_CLIENT_H
#define TRAFIKVERKET_CLIENT_H
#include <Arduino.h>

class TrafikverketClient
{
public:
    TrafikverketClient(const String &serverKey, const String &serverUrl);
    ~TrafikverketClient();

    String getTrainAnnouncements(const String &stationCode);

private:
    String m_authKey;
    String m_serverUrl;
};

#endif // TRAFIKVERKET_CLIENT_H