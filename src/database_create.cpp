#include "database_create.h"

namespace
{
    std::unique_ptr<mongo::DBClientConnection> createConnection() 
    {
        try 
        {
            std::unique_ptr<mongo::DBClientConnection> connect( new mongo::DBClientConnection() );
            connect->connect("localhost");
            return connect;
        } catch(std::exception& e) 
        {
            std::cerr << e.what() << std::endl;
        }
            return nullptr;
        }
}
DataBaseCreation::DataBaseCreation(): connection(createConnection())
    {
    }
