#include "managerdb.h"

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
    m_daoLoginInfo.connect();
    m_daoLoginInfo.createLoginInfoTable();
}
