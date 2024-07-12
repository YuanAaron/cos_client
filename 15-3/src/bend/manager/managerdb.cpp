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
    m_loginInfoList = m_daoLoginInfo.select();
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
        //更新缓存
        m_loginInfoList[indexOfLoginInfo(info.secretId)] = info;
    }
    else
    {
        m_daoLoginInfo.insert(info);
        //更新缓存
        m_loginInfoList.append(info);
    }
}

void ManagerDB::removeLoginInfo(const QString &id)
{
    if (m_daoLoginInfo.exists(id))
    {
        m_daoLoginInfo.remove(id);
        //更新缓存
        m_loginInfoList.removeAt(indexOfLoginInfo(id));
    }
}

int ManagerDB::indexOfLoginInfo(const QString &secretId)
{
    for(int i=0; i<m_loginInfoList.size(); i++)
    {
        if(m_loginInfoList[i].secretId==secretId)
        {
            return i;
        }
    }
    throw QString::fromLocal8Bit("从缓存获取登录信息失败：%1").arg(secretId);
}
