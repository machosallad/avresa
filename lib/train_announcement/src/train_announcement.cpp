#include "train_announcement.h"

const String TrainAnnouncement::stationCodes[NUM_STATIONS] = {"Lp", "Nr", "K", "Et", "Vå", "Cst", "Arnc", "U", "Fln", "Rt", "Kbä", "Ksus", "Blgc", "St", "Hdm", "Avky", "Må", "Hy"};
const String TrainAnnouncement::stationNames[NUM_STATIONS] = {
    "Linköping",
    "Norrköping",
    "Katrineholm",
    "Eskilstuna",
    "Västerås",
    "Stockholm",
    "Arlanda",
    "Uppsala",
    "Falun",
    "Ransta",
    "Kolbäck",
    "Kvicksund",
    "Borlänge",
    "Säter",
    "Hedemora",
    "Avesta Krylbo",
    "Heby",
    "Morgongåva"};

String TrainAnnouncement::getStationName(const String &stationCode)
{
    for (int i = 0; i < NUM_STATIONS; i++)
    {
        if (stationCodes[i] == stationCode)
        {
            return stationNames[i];
        }
    }
    return String("Unknown station");
}

TrainAnnouncement::TrainAnnouncement()
{
    m_ActivityType = "";
    m_AdvertisedTimeAtLocation = "";
    m_EstimatedTimeAtLocation = "";
    m_InformationOwner = "";
    m_TrackAtLocation = "";
    m_FromLocation = "";
    m_ToLocation = "";
    m_IsDelayed = false;
}

void TrainAnnouncement::updateAnnouncement(const JsonObject &json)
{
    // Print the JSON object in a pretty way
    String prettyJson;
    serializeJsonPretty(json, prettyJson);
    Serial.println(prettyJson);

    m_IsDelayed = true;
    m_ActivityType = json["ActivityType"].as<String>();
    m_InformationOwner = json["InformationOwner"].as<String>();
    m_TrackAtLocation = json["TrackAtLocation"].as<String>();
    m_AdvertisedTimeAtLocation = json["AdvertisedTimeAtLocation"].as<String>();
    if (json["EstimatedTimeAtLocation"].isNull())
    {
        m_IsDelayed = false;
        m_EstimatedTimeAtLocation = m_AdvertisedTimeAtLocation;
    }
    else
    {
        m_EstimatedTimeAtLocation = json["EstimatedTimeAtLocation"].as<String>();
    }

    JsonArray fromLocationArray = json["FromLocation"].as<JsonArray>();
    if (fromLocationArray.size() > 0)
    {
        m_FromLocation = fromLocationArray[0].as<String>();
    }

    JsonArray toLocationArray = json["ToLocation"].as<JsonArray>();
    if (toLocationArray.size() > 0)
    {
        m_ToLocation = toLocationArray[0].as<String>();
    }
}

TrainAnnouncement::TrainAnnouncement(const JsonObject &json)
{
    updateAnnouncement(json);
}

TrainAnnouncement::~TrainAnnouncement()
{
    // Destructor implementation
}

String TrainAnnouncement::getActivityType()
{
    return m_ActivityType;
}

String TrainAnnouncement::getAdvertisedTimeAtLocation()
{
    return m_AdvertisedTimeAtLocation;
}

String TrainAnnouncement::getEstimatedTimeAtLocation()
{
    return m_EstimatedTimeAtLocation;
}

String TrainAnnouncement::getInformationOwner()
{
    return m_InformationOwner;
}

String TrainAnnouncement::getTrackAtLocation()
{
    return m_TrackAtLocation;
}

String TrainAnnouncement::getFromLocation()
{
    return m_FromLocation;
}

String TrainAnnouncement::getToLocation()
{
    return m_ToLocation;
}

void TrainAnnouncement::printAll() const
{
    Serial.println("Activity Type: " + m_ActivityType);
    Serial.println("Advertised Time At Location: " + m_AdvertisedTimeAtLocation);
    Serial.println("Estimated Time At Location: " + m_EstimatedTimeAtLocation);
    Serial.println("Is Delayed: " + String(m_IsDelayed));
    Serial.println("Information Owner: " + m_InformationOwner);
    Serial.println("Track At Location: " + m_TrackAtLocation);
    Serial.println("From Location: " + getStationName(m_FromLocation));
    Serial.println("To Location: " + getStationName(m_ToLocation));
}

bool TrainAnnouncement::isDelayed() const
{
    return m_IsDelayed;
}
