#include "train_announcement_string_builder.h"

TrainAnnouncementStringBuilder &TrainAnnouncementStringBuilder::addTime(const String &time)
{
    m_string += time.substring(11, 16);
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

TrainAnnouncementStringBuilder &TrainAnnouncementStringBuilder::addSpace(bool condition)
{
    if (condition)
    {
        m_string += " ";
    }
    return *this;
}

TrainAnnouncementStringBuilder &TrainAnnouncementStringBuilder::addOwner(const String &owner)
{
    m_string += owner;
    return *this;
}

TrainAnnouncementStringBuilder &TrainAnnouncementStringBuilder::addEstimatedTime(const String &estimatedTime, bool isDelayed)
{
    if (isDelayed)
    {
        m_string += estimatedTime.substring(11, 16);
    }
    return *this;
}

TrainAnnouncementStringBuilder &TrainAnnouncementStringBuilder::addCanceled(const bool &isCanceled, const String &deviationCode)
{
    if (isCanceled)
    {
        if (deviationCode == "Buss ersätter")
        {
            m_string += "Buss";
        }
        else
        {
            m_string += "Inställd";
        }
    }
    return *this;
}

String TrainAnnouncementStringBuilder::build() const
{
    return m_string;
}
