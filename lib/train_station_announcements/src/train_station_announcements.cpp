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

// Instead of parsing the JSON data in one go, we will parse the JSON data in chunks and store the station names in a map.
// This will allow us to update the station names without having to parse the entire JSON data again.
void TrainStationAnnouncements::updateStationNames(const String &jsonString)
{
    m_stationNames.clear(); // Clear the current list of station names

    // Find the start and end of the TrainStation object array
    int arrayStart = jsonString.indexOf("\"TrainStation\"");
    if (arrayStart == -1)
    {
        Serial.println("Invalid JSON data, no TrainStation object found");
        return;
    }

    // Find the start of the array
    arrayStart = jsonString.indexOf('[', arrayStart);
    if (arrayStart == -1)
    {
        Serial.println("Invalid JSON data, start of TrainStation array not found");
        return;
    }

    // Adjust the start position to the start of the array elements
    arrayStart = jsonString.indexOf('{', arrayStart);
    if (arrayStart == -1)
    {
        Serial.println("Invalid JSON data, start of TrainStation array elements not found");
        return;
    }

    // Loop over the array elements
    int elementStart = arrayStart;
    while (elementStart != -1 && elementStart < jsonString.length())
    {
        // Find the end of the next element
        int elementEnd = jsonString.indexOf('}', elementStart) + 1;
        if (elementEnd == 0)
        {
            Serial.println("Invalid JSON data, end of TrainStation array element not found");
            return;
        }

        // Extract the element JSON
        String elementJson = jsonString.substring(elementStart, elementEnd);

        // Parse the element JSON
        StaticJsonDocument<MAX_JSON_SIZE> doc;
        DeserializationError error = deserializeJson(doc, elementJson);
        if (error)
        {
            Serial.println("Failed to parse JSON");
            return;
        }

        // Extract the station code and name
        String stationCode = doc["LocationSignature"];
        String stationName = doc["AdvertisedLocationName"];
        m_stationNames[stationCode] = stationName;

        // Move to the next element
        elementStart = jsonString.indexOf('{', elementEnd);
        Serial.println("{\"" + stationCode + "\",\"" + stationName + "\"},");
    }

    Serial.println("Number of stations: " + String(m_stationNames.size()) + " stations.");
}

String TrainStationAnnouncements::getStationName(const String &stationCode) const
{
    auto it = m_stationNames.find(stationCode);
    if (it != m_stationNames.end())
    {
        return it->second;
    }
    return String(stationCode);
}
