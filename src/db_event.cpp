#include "database.h"
#include "database_create.h"
#include "db_event.h"

#include <mongo/client/dbclient.h>

        
bool DbEvent::getEventById(const std::string& id)
{
    const mongo::Query& q = mongo::Query( BSON("_id" << mongo::OID(id) ) );
    const auto& fields = BSON("_id" << 1 << "data" << 1);
    const auto& b = db->getConnection()->findOne("test.images", q, &fields);
    if (b.isEmpty()) 
    {
        return false;
    }

    int len;
    const char* ptr = b["data"].binData(len);
    this->data = std::string(ptr, len);
    this->id = id;
    return true;
}

void DbEvent::insertEvent(const std::string& data)
{
    const mongo::BSONObj& bos = mongo::BSONObjBuilder().genOID().append("event", "").obj();
    mongo::DBClientConnection *conn;
    conn = db->getConnection();
    conn->insert("test.event", bos);
}

size_t DbEvent::getSize() const
{
    return data.length();
}

const char* DbEvent::getEventData(size_t& len) const
{
    len = data.size();
    return data.c_str();
}

const std::string& DbEvent::getId() const
{
    return id;
}

