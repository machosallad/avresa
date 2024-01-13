#include "train_announcement.h"

const std::map<String, String> TrainAnnouncement::stationMap = {
    {"Lp", "Linköping"},
    {"Nr", "Norrköping"},
    {"K", "Katrineholm"},
    {"Et", "Eskilstuna"},
    {"Vå", "Västerås"},
    {"Cst", "Stockholm C"},
    {"Arnc", "Arlanda"},
    {"U", "Uppsala"},
    {"Fln", "Falun"},
    {"Rt", "Ransta"},
    {"Kbä", "Kolbäck"},
    {"Ksus", "Kvicksund"},
    {"Blgc", "Borlänge"},
    {"St", "Säter"},
    {"Hdm", "Hedemora"},
    {"Avky", "Avesta Krylbo"},
    {"Må", "Morgongåva"},
    {"Hy", "Heby"},
    {"Sl", "Sala"},
    {"Mrc", "Mora"}};

String TrainAnnouncement::getStationName(const String &stationCode)
{
    auto it = stationMap.find(stationCode);
    if (it != stationMap.end())
    {
        return it->second;
    }
    return String(stationCode);
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
        // The first element in the array is where the train is coming from
        m_FromLocation = fromLocationArray[0].as<String>();
    }

    JsonArray toLocationArray = json["ToLocation"].as<JsonArray>();
    if (toLocationArray.size() > 0)
    {
        // The last element in the array is the final destination
        m_ToLocation = toLocationArray[toLocationArray.size() - 1].as<String>();
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
    String hourAndMinute = m_AdvertisedTimeAtLocation.substring(11, 16);
    return hourAndMinute;
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
