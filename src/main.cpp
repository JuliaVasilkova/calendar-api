#include "events.h"

#include <fastcgi2/component.h>
#include <fastcgi2/component_factory.h>
#include <fastcgi2/handler.h>
#include <fastcgi2/request.h>

#include <iostream>
#include <sstream>

class EventFastCGI : virtual public fastcgi::Component, virtual public fastcgi::Handler
{
    public:
        EventFastCGI(fastcgi::ComponentContext *context) :
                     fastcgi::Component(context)
        {

        }

        virtual void onLoad()
        { 

        }

        virtual void onUnload()
        {

        } 

        virtual void handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context)
        {
            events.ScheduleRequest(request, context);

                /*request->setContentType("text/plain");
                std::stringbuf buffer("Hello " + (request->hasArg("name") ? request->getArg("name") : "world!"));
                request->write(&buffer);
                */
        }
    private:
        NEvents::Events events;
};

FCGIDAEMON_REGISTER_FACTORIES_BEGIN()
FCGIDAEMON_ADD_DEFAULT_FACTORY("EventFastCGIFactory", EventFastCGI)
FCGIDAEMON_REGISTER_FACTORIES_END()
