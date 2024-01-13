#ifndef ANNOUNCEMENTS_H
#define ANNOUNCEMENTS_H

#include "train_announcement.h"
#include <ArduinoJson.h>

#define MAX_ANNOUNCEMENTS 10   // Maximum number of announcements
#define MAX_JSON_SIZE 2048 * 2 // Maximum size of JSON string

class Announcements
{
public:
    Announcements(); // Default constructor
    Announcements(const String &jsonString);
    ~Announcements();

    void updateAnnouncements(const String &jsonString);
    void printAll() const;
    TrainAnnouncement getAnnouncement(int index) const;
    int getNumAnnouncements() const;

private:
    TrainAnnouncement trainAnnouncements[MAX_ANNOUNCEMENTS]; // Array of TrainAnnouncement objects
    int numAnnouncements;                                    // Number of announcements currently in the array
};

#endif // ANNOUNCEMENTS_H