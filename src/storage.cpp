#include "storage.h"

#include <time.h>
#include <stdio.h>
#include <string.h>





bool EventStorage::EventDateComparator::operator()(const time_t& _Left, const time_t& _Right) const

{

	tm temp1;

	tm* pT = localtime(&_Left);



	if(pT != NULL)

		temp1 = *pT;

	else

		memset(&temp1, 0, sizeof(tm));



	tm temp2;



	pT = localtime(&_Right);

	if(pT != NULL)

		temp2 = *pT;

	else

		memset(&temp2, 0, sizeof(tm));



	if(temp1.tm_year < temp2.tm_year)

		return true;

	else if(temp1.tm_year == temp2.tm_year)

		return	temp1.tm_yday < temp2.tm_yday;

	else

		return false;

}



bool EventStorage::GetEvents(time_t eventId, Infos& infos)

{

	auto begin = m_events.lower_bound(eventId);



	if(begin != m_events.end())

	{

		auto end = m_events.upper_bound(eventId);

		for(; begin != end; ++begin)

			infos.push_back(begin->second);



		return true;

	}



	return false;

}



bool EventStorage::GetEventById(const std::string& eventId, EventInfo& info)

{

	for(const auto& val : m_events)

	{

		if( strcmp(val.second.eventID.c_str(), eventId.c_str()) == 0)

		{

			info = val.second;

			return true;

		}

	}



	return false;

}



bool EventStorage::AddEvent(const EventInfo& info)

{

	m_events.insert(std::make_pair(info.rase_at, info));

	return true;

}



