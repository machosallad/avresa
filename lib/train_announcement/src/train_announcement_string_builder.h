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
    TrainAnnouncementStringBuilder &addSpace(bool condition);
    TrainAnnouncementStringBuilder &addOwner(const String &informationOwner);
    TrainAnnouncementStringBuilder &addEstimatedTime(const String &estimatedTime, bool isDelayed);
    TrainAnnouncementStringBuilder &addCanceled(const bool &isCanceled, const String &deviationCode);
    String build() const;

private:
    String m_string;
};

#endif // TRAIN_ANNOUNCEMENT_STRING_BUILDER_H