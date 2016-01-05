#include "database_create.h"
#include "database.h"

DataBase::DataBase()
{
    db_creator = new DataBaseCreation();
}

DataBase::~DataBase()
{
    delete db_creator;
}
