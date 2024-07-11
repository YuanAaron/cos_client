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
    createLoginInfoTable();
}

void ManagerDB::connect()
{
    m_db.connect(CONFIG::SQLITE::NAME);
}

void ManagerDB::createLoginInfoTable()
{
    QString sql = FileHelper::readAllTxt(CONFIG::SQL::LOGIN_INFO_TABLE);
    m_db.exec(sql);
}
