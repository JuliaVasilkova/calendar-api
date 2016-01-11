#pragma once
#include <map>

#include <vector>

#include "data.h"





class EventStorage {



    struct EventDateComparator

    {

        bool operator()(const time_t& _Left, const time_t& _Right) const;

    };



public:

    typedef std::vector<EventInfo> Infos;



    bool GetEvents   (time_t time, Infos& infos);

    bool GetEventById   (const std::string& eventId, EventInfo& info);

    bool AddEvent   (const EventInfo& info);

private:

    std::multimap<time_t, EventInfo, EventDateComparator> m_events;

};