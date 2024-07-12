#include "dbsqlite.h"

#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

DBSqlite::DBSqlite()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
}

DBSqlite::~DBSqlite()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

void DBSqlite::connect(const QString &DBPath)
{
    m_db.setDatabaseName(DBPath);
    //m_db.setHostName();
    //m_db.setPort();
    //m_db.setUserName();
    //m_db.setPassword();
    if (!m_db.open())
    {
        throw QString::fromLocal8Bit("打开数据库失败：%1 %2").arg(DBPath, m_db.lastError().text());
    }
}

QSqlQuery DBSqlite::exec(const QString &sql)
{
    QSqlQuery query;
    if(!query.exec(sql))
    {
        throw QString::fromLocal8Bit("执行sql失败：%1 %2").arg(sql, m_db.lastError().text());
    }
    return query;
}

bool DBSqlite::exists(const QString &secretId)
{
    QSqlQuery query = exec(secretId);
    return query.next(); //是否有数据
}

QList<RECORD> DBSqlite::select(const QString& sql)
{
    QList<RECORD> retList;
    QSqlQuery query = exec(sql);

    while (query.next())
    {
        RECORD ret;
        QSqlRecord record = query.record();  // 数据库中的一行记录
        for (int i = 0; i < record.count(); i++)
        {
            QString name = record.fieldName(i);
            QVariant value = record.value(i);
            ret[name] = value;
        }
        qDebug() << QString::fromLocal8Bit("查询出结果:")  << ret;
        retList.append(ret);
    }
    return retList;
}
