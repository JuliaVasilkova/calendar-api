#pragma once

#include <fastcgi2/handler.h>
#include <fastcgi2/request.h>

#include <string>
#include "storage.h"

namespace NEvents
{
class Events
{
	public:
		Events(){}
		void ScheduleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context);
	private:
		void EventCreate(fastcgi::Request *request, fastcgi::HandlerContext *context);
		void GetEventInfo(fastcgi::Request *request, fastcgi::HandlerContext *context, const std::string& eventId);
		//void EventUpdate(fastcgi::Request *request, fastcgi::HandleContext *context);
		void TodayEvents(fastcgi::Request *request, fastcgi::HandlerContext *context);
		EventStorage storage;
};
}