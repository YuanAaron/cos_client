#include "dbsqlite.h"

#include <QSqlError>

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
