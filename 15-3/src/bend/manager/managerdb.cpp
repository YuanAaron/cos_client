#include "managerdb.h"

#include <QDateTime>

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

void ManagerDB::saveLoginInfo(const QString &name, const QString &id, const QString &key, const QString remark)
{
    LoginInfo info;
    info.name = (name == "" ? id.trimmed() : name.trimmed());
    info.secretId = id.trimmed();
    info.secretKey = key.trimmed();
    info.remark = remark.trimmed();
    info.timestamp = QDateTime::currentDateTimeUtc().toTime_t();

    if (m_daoLoginInfo.exists(info.secretId))
    {
        m_daoLoginInfo.update(info);
    }
    else
    {
        m_daoLoginInfo.insert(info);
    }
}

void ManagerDB::removeLoginInfo(const QString &id)
{
    if (m_daoLoginInfo.exists(id))
    {
        m_daoLoginInfo.remove(id);
    }
}
