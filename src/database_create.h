#pragma once

#include <sstream>
#include <iostream>
#include <mongo/client/dbclient.h>
#include <memory>

class DataBaseCreation
{
    public:
        DataBaseCreation();
        ~DataBaseCreation();
        mongo::DBClientConnection* getConnection() 
        {
            return connection.get();
        }

    private:
        std::unique_ptr<mongo::DBClientConnection> connection;
};
