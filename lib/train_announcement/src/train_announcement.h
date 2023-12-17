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
    String getAdvertisedTimeAtLocation();
    String getEstimatedTimeAtLocation();
    String getInformationOwner();
    String getTrackAtLocation();
    String getFromLocation();
    String getToLocation();
    void printAll() const;
    bool isDelayed() const;

    static String getStationName(const String &stationCode);
    void updateAnnouncement(const JsonObject &json);

private:
    String m_ActivityType;
    String m_AdvertisedTimeAtLocation;
    String m_EstimatedTimeAtLocation;
    String m_InformationOwner;
    String m_TrackAtLocation;
    String m_FromLocation;
    String m_ToLocation;
    bool m_IsDelayed;

    static const std::map<String, String> stationMap;
};

#endif // TRAIN_ANNOUNCEMENT_H