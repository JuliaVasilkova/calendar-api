#pragma once

#include <ctime>
#include <string>

struct EventInfo
{
	EventInfo	( const std::string& id = "", time_t rase = 0, time_t remind = 0): 
				eventID(id),
				rase_at(rase)
				{}
	std::string eventID;
	time_t rase_at;
};