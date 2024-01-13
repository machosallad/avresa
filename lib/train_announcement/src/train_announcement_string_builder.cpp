#include "train_announcement_string_builder.h"

TrainAnnouncementStringBuilder &TrainAnnouncementStringBuilder::addTime(const String &time)
{
    m_string += time;
    return *this;
}

TrainAnnouncementStringBuilder &TrainAnnouncementStringBuilder::addStationName(const String &stationName)
{
    m_string += stationName;
    return *this;
}

TrainAnnouncementStringBuilder &TrainAnnouncementStringBuilder::addTrack(const String &track)
{
    m_string += track;
    return *this;
}

TrainAnnouncementStringBuilder &TrainAnnouncementStringBuilder::addSpace()
{
    m_string += " ";
    return *this;
}

TrainAnnouncementStringBuilder &TrainAnnouncementStringBuilder::addInformationOwner(const String &informationOwner)
{
    m_string += informationOwner;
    return *this;
}

String TrainAnnouncementStringBuilder::build() const
{
    return m_string;
}
