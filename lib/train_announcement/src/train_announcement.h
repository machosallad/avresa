#ifndef TRAIN_ANNOUNCEMENT_H
#define TRAIN_ANNOUNCEMENT_H

#include <ArduinoJson.h>
#include <Arduino.h>
#include <map>

class TrainAnnouncement
{
public:
    TrainAnnouncement(); // Default constructor
    TrainAnnouncement(const JsonObject &json);
    ~TrainAnnouncement();

    String getActivityType();
    String getAdvertisedTime();
    String getEstimatedTime();
    String getOwner();
    String getTrackAtLocation();
    String getFromLocation();
    String getToLocation();
    void printAll() const;
    bool isDelayed() const;

    static String getStationName(const String &stationCode);
    void updateAll(const JsonObject &json);

private:
    String m_activityType;
    String m_advertisedTime;
    String m_estimatedTime;
    String m_owner;
    String m_track;
    String m_fromLocation;
    String m_toLocation;
    bool m_isDelayed;

    static const std::map<String, String> m_stationMap;
};

#endif // TRAIN_ANNOUNCEMENT_H