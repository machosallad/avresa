#ifndef XML_REQUESTS_H
#define XML_REQUESTS_H

#include <Arduino.h>

// Define your XML requests here
String TRAIN_ANNOUNCEMENT_REQUEST(String auth_key, String station_code)
{
    String xml =
        "<REQUEST>\n"
        "\t<LOGIN authenticationkey='AUTH_KEY_PLACEHOLDER' />\n"
        "\t<QUERY objecttype='TrainAnnouncement' orderby='AdvertisedTimeAtLocation' schemaversion='1' limit='4'>\n"
        "\t\t<FILTER>\n"
        "\t\t\t<AND>\n"
        "\t\t\t\t<OR>\n"
        "\t\t\t\t\t<AND>\n"
        "\t\t\t\t\t\t<GT name='AdvertisedTimeAtLocation' value='$dateadd(00:00:00)' />\n"
        "\t\t\t\t\t\t<LT name='AdvertisedTimeAtLocation' value='$dateadd(10:00:00)' />\n"
        "\t\t\t\t\t</AND>\n"
        "\t\t\t\t\t<GT name='EstimatedTimeAtLocation' value='$now' />\n"
        "\t\t\t\t</OR>\n"
        "\t\t\t\t<EQ name='LocationSignature' value='STATION_CODE_PLACEHOLDER' />\n"
        "\t\t\t\t<EQ name='ActivityType' value='Avgang' />\n"
        "\t\t\t</AND>\n"
        "\t\t</FILTER>\n"
        "\t\t<INCLUDE>InformationOwner</INCLUDE>\n"
        "\t\t<INCLUDE>AdvertisedTimeAtLocation</INCLUDE>\n"
        "\t\t<INCLUDE>TrackAtLocation</INCLUDE>\n"
        "\t\t<INCLUDE>FromLocation</INCLUDE>\n"
        "\t\t<INCLUDE>ToLocation</INCLUDE>\n"
        "\t\t<INCLUDE>ActivityType</INCLUDE>\n"
        "\t\t<INCLUDE>EstimatedTimeAtLocation</INCLUDE>\n"
        "\t</QUERY>\n"
        "</REQUEST>\n";

    xml.replace("AUTH_KEY_PLACEHOLDER", auth_key);
    xml.replace("STATION_CODE_PLACEHOLDER", station_code);
    return xml;
}
#endif // REQUESTS_H