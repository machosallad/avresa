#ifndef STATION_LOOKUP_H
#define STATION_LOOKUP_H

#include <Arduino.h>

struct Station
{
    String code;
    String name;
};

class StationLookup
{
public:
    static StationLookup &getInstance();

    String getStationName(const String &code);
    static const size_t numStations;
    Station getStation(size_t index);

private:
    StationLookup();                                // Constructor is private
    StationLookup(const StationLookup &) = delete;  // Prevent copy constructor
    void operator=(const StationLookup &) = delete; // Prevent assignment
};
#endif // STATION_LOOKUP_H