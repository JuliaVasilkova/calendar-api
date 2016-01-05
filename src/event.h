#include <fastcgi2/component.h>
#include <fastcgi2/component_factory.h>
#include <fastcgi2/handler.h>
#include <fastcgi2/request.h>

#include <iostream>
#include <sstream>

class EventHandler : virtual public fastcgi::Component, virtual public fastcgi::Handler
{
    public:
        EventHandler(fastcgi::ComponentContext *context) :
                     fastcgi::Component(context)
        {}

	virtual ~EventHandler(){} 
	
        virtual void onLoad()
        { 
        }

        virtual void onUnload()
        {
        } 

        virtual void handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context);
};
