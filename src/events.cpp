
#include <fastcgi2/stream.h>
#include <fastcgi2/component.h>
#include <fastcgi2/component_factory.h>
#include <fastcgi2/handler.h>
#include <fastcgi2/request.h>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>

#include <iomanip>
#include <iostream>
#include <ctime>
#include <sstream>

#include "events.h"
#include "data.h"
#include "storage.h"

namespace {

	const size_t EVENT_PREFIX_SIZE = sizeof("/events/") - 1;

	std::time_t StringToDate( std::string& date)
	{
		struct tm tm;
		memset(&tm, 0, sizeof(struct tm));
		const char * cstr = date.c_str();
		strptime(cstr, "%Y-%m-%d %H:%M:%S", &tm);
		return mktime(&tm);  // t is now your desired time_t
	}

	std::string DateToString( const time_t& date)
	{
		//std::stringstream ss;
    	//ss << date;
    	char str_buff[80];
    	strftime(str_buff, 80, "%Y-%m-%d %H:%M:%S", localtime(&date));
    	std::string str(str_buff, strnlen(str_buff, 80));
    	return str;
	}

	bool IsTodayEvents(const std::string& path, const std::string& method) 
	{
    	return path == "/events" && method == "GET";
	}

	bool IsEventCreate(const std::string& path, const std::string& method) 
	{
    	return path == "/events" && method == "PUT";
    	/*if(method == "PUT" &&
    		path.find("/events/") == 0 &&
    		path.find('/', EVENT_PREFIX_SIZE) == std::string::npos)
    	{
    		std::string st_date = DateToString(date);
    		st_date = path.substr(EVENT_PREFIX_SIZE);
    		return true;
    	}
    	return false;
    	*/
	}

	bool IsEventInfo(const std::string& path, const std::string& method, std::string* event_name) 
	{
    	if (method == "GET" &&
        	path.find("/events/") == 0 && path.find('/', EVENT_PREFIX_SIZE) == std::string::npos)
    	{
        	*event_name = path.substr(EVENT_PREFIX_SIZE);
        	return true;
    	}
    	return false;
	}



	void PrintEventInfo	(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer,
                      	const EventInfo& eventInfo)
	{
    	writer.StartObject();
    	writer.String("event_name");
    	writer.String(eventInfo.eventID.c_str());
    	writer.String("event_date");
    	std::string ts = DateToString(eventInfo.rase_at);
    	writer.String(ts.c_str());
    	writer.EndObject();
	}

}

namespace NEvents
{
	void Events::ScheduleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context)
	{
		auto& path = request->getScriptName();
		auto& method = request->getRequestMethod();
		request->setContentType("application/json");

		std::string event_name;
		//time_t event_date;

		if (IsTodayEvents(path, method)) 
		{
        	TodayEvents(request, context);
    	}
    	else if (IsEventCreate(path, method)) 
    	{
        	EventCreate(request, context);
    	} 
    	else if (IsEventInfo(path, method, &event_name)) 
    	{
        	GetEventInfo(request, context, event_name);
    	} 
    	else 
    	{
        	request->setStatus(404);
    	}
	}

	void Events::EventCreate(fastcgi::Request *request, fastcgi::HandlerContext *context)
	{
		fastcgi::RequestStream stream(request);

		std::string inputJson;
		request->requestBody().toString(inputJson);
    	rapidjson::Document document;
    	if(document.Parse(inputJson.c_str()).HasParseError() )
    	{
    		stream << "[\" json Parse error \"]";
    		request->setStatus(400);
    		return;
    	}
    	else if (!(document.HasMember("event_name") && document["event_name"].IsString() &&
    				document.HasMember("event_date")))
		{
			stream << "[\" json doesn't have required fields \"]";
			request->setStatus(400);
			return;
		}

		EventInfo event;
		event.eventID = document["event_name"].GetString();
		std::string event_date_str = document["event_date"].GetString();
		std::time_t event_d = StringToDate(event_date_str);
		event.rase_at = event_d;
		bool st = storage.AddEvent(event);
		if(!st)
		{
			request->setStatus(400);
		}
		rapidjson::StringBuffer sb;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
		PrintEventInfo(writer, event);
		request->write(sb.GetString(), sb.GetSize());
		request->setStatus(200);
	}

	void Events::GetEventInfo(fastcgi::Request *request, fastcgi::HandlerContext *context, const std::string& eventId)
	{
		EventInfo event;
		bool st = storage.GetEventById(eventId, event);
		if(!st)
		{
			request->setStatus(404);
			return;
		}

		rapidjson::StringBuffer sb;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
		PrintEventInfo(writer, event);
		request->write(sb.GetString(), sb.GetSize());
		request->setStatus(200);
	}

	void Events::TodayEvents(fastcgi::Request *request, fastcgi::HandlerContext *context)
	{

		fastcgi::RequestStream stream(request);
		stream << "[\"Today events \"]";

		std::vector<EventInfo> events;
		//td::string now = "2016-11-01";
		time_t raw_time = time(NULL);
		//std::string timeinfo = DateToString(raw_time);
		//time(&raw_time);
		//timeinfo = localtime(&raw_time);
		bool st = storage.GetEvents(raw_time, events);
		//stream << "today: " << timeinfo;
		if(!st)
		{
			request->setStatus(404);
			return;
		}

		rapidjson::StringBuffer sb;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
		writer.StartObject();
		writer.String("today_events");
		writer.StartArray();
		for (const auto& event : events)
		{
			PrintEventInfo(writer, event);
			stream << "event: " << event.eventID << "  date: " << event.rase_at;
		}
		writer.EndArray();
		writer.EndObject();

		request->write(sb.GetString(), sb.GetSize());
		request->setStatus(200);
	}
}