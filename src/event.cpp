#include <fastcgi2/component.h>
#include <fastcgi2/component_factory.h>
#include <fastcgi2/handler.h>
#include <fastcgi2/request.h>

#include "db_event.h"
#include "event.h"
#include <iostream>
#include <sstream>

DataBase my_db;

void EventHandler::handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context)
{
	if(request->getRequestMethod() == "POST")
	{
        const auto& filename = request->getScriptFilename();
        if(filename != "/event/")
        {
            return request->sendError(400);
        }
        if(request->hasFile("event"))
        {
            std::string data;
            request->remoteFile("event").toString(data);
            DbEvent event(my_db);
            event.insertEvent(data);
            request->setHeader("Location", std::string("/event/") + event.getId());
            return request->setStatus(302); //redirect
        }
        else
        {
            return request->sendError(400); // wrong format
        }
	    //request->setContentType("text/plain");
        //std::stringbuf buffer("Your new event is " + request->getArg("name"));
        //request->write(&buffer);
	}
    else
    {
        return request->sendError(405); //invalid method`
    }
	

}
