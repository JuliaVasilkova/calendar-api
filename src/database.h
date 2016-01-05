#pragma once

#include <mongo/client/dbclient.h>
#include <memory>

class DataBaseCreation;

class DataBase
{
    public:
        DataBase();
        ~DataBase();
        
        DataBaseCreation* operator->() const
        {
            return db_creator;
        }
    private:
        DataBaseCreation* db_creator;
};
