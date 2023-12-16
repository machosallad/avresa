#include "announcements.h"

Announcements::Announcements() : numAnnouncements(0)
{
}

Announcements::Announcements(const String &jsonString) : numAnnouncements(0)
{
    updateAnnouncements(jsonString);
}

Announcements::~Announcements()
{
}

void Announcements::updateAnnouncements(const String &jsonString)
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

void Announcements::printAll() const
{
    for (int i = 0; i < numAnnouncements; ++i)
    {
        Serial.println("====================================="); // Print a separator
        trainAnnouncements[i].printAll();
    }
}
