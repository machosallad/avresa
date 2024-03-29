#include "train_announcement.h"

const std::map<String, String> TrainAnnouncement::m_stationMap = {
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
    {"Mrc", "Mora"},
    {"Uå", "Umeå C"},
    {"M", "Malmö C"},
    {"Du", "Duved"},
    {"Hpbg", "Hallsberg"},
    {"G", "Göteborg C"}};

String TrainAnnouncement::getStationName(const String &stationCode)
{
    auto it = m_stationMap.find(stationCode);
    if (it != m_stationMap.end())
    {
        return it->second;
    }
    return String(stationCode);
}

TrainAnnouncement::TrainAnnouncement()
{
    m_activityType = "";
    m_advertisedTime = "";
    m_estimatedTime = "";
    m_owner = "";
    m_track = "";
    m_fromLocation = "";
    m_toLocation = "";
    m_isDelayed = false;
    m_isCanceled = false;
    m_deviationCode = "";
    m_deviationDescription = "";
}

void TrainAnnouncement::updateAll(const JsonObject &json)
{
    // Print the JSON object in a pretty way
    String prettyJson;
    serializeJsonPretty(json, prettyJson);

    m_isDelayed = true;
    m_activityType = json["ActivityType"].as<String>();
    m_owner = json["InformationOwner"].as<String>();
    m_track = json["TrackAtLocation"].as<String>();
    m_advertisedTime = json["AdvertisedTimeAtLocation"].as<String>();
    m_isCanceled = json["Canceled"].as<bool>();

    if (json["EstimatedTimeAtLocation"].isNull())
    {
        m_isDelayed = false;
        m_estimatedTime = m_advertisedTime;
    }
    else
    {
        m_estimatedTime = json["EstimatedTimeAtLocation"].as<String>();
    }

    JsonArray deviationArray = json["Deviation"].as<JsonArray>();
    if (deviationArray.size() > 0)
    {
        // The first element in the array is the deviation code
        m_deviationCode = deviationArray[0].as<String>();
        // The second element in the array is the deviation description
        m_deviationDescription = deviationArray[1].as<String>();
    }

    JsonArray fromLocationArray = json["FromLocation"].as<JsonArray>();
    if (fromLocationArray.size() > 0)
    {
        // The first element in the array is where the train is coming from
        m_fromLocation = fromLocationArray[0].as<String>();
    }

    JsonArray toLocationArray = json["ToLocation"].as<JsonArray>();
    if (toLocationArray.size() > 0)
    {
        // The last element in the array is the final destination
        m_toLocation = toLocationArray[toLocationArray.size() - 1].as<String>();
    }
}

TrainAnnouncement::TrainAnnouncement(const JsonObject &json)
{
    updateAll(json);
}

TrainAnnouncement::~TrainAnnouncement()
{
    // Destructor implementation
}

String TrainAnnouncement::getActivityType()
{
    return m_activityType;
}

String TrainAnnouncement::getAdvertisedTime()
{
    return m_advertisedTime;
}

String TrainAnnouncement::getEstimatedTime()
{
    return m_estimatedTime;
}

String TrainAnnouncement::getOwner()
{
    return m_owner;
}

String TrainAnnouncement::getTrackAtLocation()
{
    return m_track;
}

String TrainAnnouncement::getFromLocation()
{
    return m_fromLocation;
}

String TrainAnnouncement::getToLocation()
{
    return m_toLocation;
}

String TrainAnnouncement::getDeviationCode()
{
    return m_deviationCode;
}

String TrainAnnouncement::getDeviationDescription()
{
    return m_deviationDescription;
}

void TrainAnnouncement::printAll() const
{
    Serial.println("Activity Type: " + m_activityType);
    Serial.println("Advertised Time: " + m_advertisedTime);
    Serial.println("Estimated Time: " + m_estimatedTime);
    Serial.println("Is Delayed: " + String(m_isDelayed));
    Serial.println("Owner: " + m_owner);
    Serial.println("Track: " + m_track);
    Serial.println("From Location: " + getStationName(m_fromLocation));
    Serial.println("To Location: " + getStationName(m_toLocation));
    Serial.println("Is Canceled: " + String(m_isCanceled));
    Serial.println("Deviation Code: " + m_deviationCode);
    Serial.println("Deviation Description: " + m_deviationDescription);
}

bool TrainAnnouncement::isDelayed() const
{
    return m_isDelayed;
}

bool TrainAnnouncement::isCanceled() const
{
    return m_isCanceled;
}
