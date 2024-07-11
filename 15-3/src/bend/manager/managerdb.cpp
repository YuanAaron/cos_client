#include "managerdb.h"
#include "src/config/config.h"

Q_GLOBAL_STATIC(ManagerDB, ins)

ManagerDB::ManagerDB(QObject *parent) : QObject(parent)
{

}

ManagerDB *ManagerDB::instance()
{
    return ins();
}

void ManagerDB::init()
{
    connect();
}

void ManagerDB::connect()
{
    m_db.connect(CONFIG::SQLITE::NAME);
}
