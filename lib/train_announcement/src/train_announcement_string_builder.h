#ifndef TRAIN_ANNOUNCEMENT_STRING_BUILDER_H
#define TRAIN_ANNOUNCEMENT_STRING_BUILDER_H

#include <Arduino.h>

class TrainAnnouncementStringBuilder
{
public:
    TrainAnnouncementStringBuilder &addTime(const String &time);
    TrainAnnouncementStringBuilder &addStationName(const String &stationName);
    TrainAnnouncementStringBuilder &addTrack(const String &track);
    TrainAnnouncementStringBuilder &addSpace();
    String build() const;

private:
    String m_string;
};

#endif // TRAIN_ANNOUNCEMENT_STRING_BUILDER_H