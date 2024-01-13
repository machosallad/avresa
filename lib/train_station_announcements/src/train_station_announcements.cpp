#include "train_station_announcements.h"

TrainStationAnnouncements::TrainStationAnnouncements() : numAnnouncements(0)
{
}

TrainStationAnnouncements::TrainStationAnnouncements(const String &jsonString) : numAnnouncements(0)
{
    updateAnnouncements(jsonString);
}

TrainStationAnnouncements::~TrainStationAnnouncements()
{
}

void TrainStationAnnouncements::updateAnnouncements(const String &jsonString)
{
    // Clear the current list of TrainAnnouncement objects
    numAnnouncements = 0;

    // Parse the new JSON string and create new TrainAnnouncement objects
    StaticJsonDocument<MAX_JSON_SIZE> doc;
    deserializeJson(doc, jsonString);

    JsonArray array = doc["RESPONSE"]["RESULT"][0]["TrainAnnouncement"];
    for (JsonVariant v : array)
    {
        if (numAnnouncements >= MAX_ANNOUNCEMENTS)
            break; // Stop if the array is full
        trainAnnouncements[numAnnouncements++] = TrainAnnouncement(v.as<JsonObject>());
    }
}

void TrainStationAnnouncements::printAll() const
{
    for (int i = 0; i < numAnnouncements; ++i)
    {
        Serial.println("====================================="); // Print a separator
        trainAnnouncements[i].printAll();
    }
}

TrainAnnouncement TrainStationAnnouncements::getAnnouncement(int index) const
{
    if (index < 0 || index >= numAnnouncements)
        return TrainAnnouncement(); // Return an empty TrainAnnouncement object
    return trainAnnouncements[index];
}

int TrainStationAnnouncements::getNumAnnouncements() const
{
    return numAnnouncements;
}
