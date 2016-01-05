#pragma once

#include "database.h"
#include <stddef.h>
#include <string>

class DbEvent 
{
    public:
        DbEvent(DataBase& db): db(db){}
        
        bool getEventById(const std::string& id);
        void insertEvent(const std::string& data);
        size_t getSize() const;
        const char* getEventData(size_t& len) const;
        const std::string& getId() const;

    private:
        std::string data;
        std::string id;
        const DataBase& db;
};
