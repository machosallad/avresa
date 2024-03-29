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
    String getDeviationCode();
    String getDeviationDescription();
    void printAll() const;
    bool isDelayed() const;
    bool isCanceled() const;

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
    String m_deviationCode;
    String m_deviationDescription;
    bool m_isDelayed;
    bool m_isCanceled;

    static const std::map<String, String> m_stationMap;
};

#endif // TRAIN_ANNOUNCEMENT_H