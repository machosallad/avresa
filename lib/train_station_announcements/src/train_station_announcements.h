#ifndef TRAIN_STATION_ANNOUNCEMENTS_H
#define TRAIN_STATION_ANNOUNCEMENTS_H

#include "train_announcement.h"
#include <ArduinoJson.h>
#include <map>

#define MAX_ANNOUNCEMENTS 10   // Maximum number of announcements
#define MAX_JSON_SIZE 2048 * 2 // Maximum size of JSON string

class TrainStationAnnouncements
{
public:
    TrainStationAnnouncements(); // Default constructor
    TrainStationAnnouncements(const String &jsonString);
    ~TrainStationAnnouncements();

    void updateStationNames(const String &jsonString);
    String getStationName(const String &stationCode) const;
    void updateAnnouncements(const String &jsonString);
    void printAll() const;
    TrainAnnouncement getAnnouncement(int index) const;
    int getNumAnnouncements() const;

private:
    TrainAnnouncement trainAnnouncements[MAX_ANNOUNCEMENTS]; // Array of TrainAnnouncement objects
    int numAnnouncements;                                    // Number of announcements currently in the array
    std::map<String, String> m_stationNames;
};

#endif // TRAIN_STATION_ANNOUNCEMENTS_H