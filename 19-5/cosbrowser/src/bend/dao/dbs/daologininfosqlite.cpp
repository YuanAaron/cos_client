#include "daologininfosqlite.h"
#include "src/config/config.h"

DaoLoginInfoSqlite::DaoLoginInfoSqlite()
{

}

void DaoLoginInfoSqlite::connect()
{
    m_db.connect(CONFIG::SQLITE::NAME);
}

void DaoLoginInfoSqlite::createLoginInfoTable()
{
    QString sql = FileHelper::readAllTxt(CONFIG::SQL::LOGIN_INFO_TABLE);
    m_db.exec(sql);
}

//bool DaoLoginInfoSqlite::exists(const QString &secretId)
//{
//    QString sql = QString(
//                      "select id from %1 where  "
//                      "secret_id = '%2';")
//                      .arg(CONFIG::TABLES::LOGIN_INFO, secretId);
//    return m_db.exists(sql);
//}

bool DaoLoginInfoSqlite::exists(const QString &secretId)
{
    QString sql = QString(
                      "select id from %1 where  "
                      "secret_id = ?")
                      .arg(CONFIG::TABLES::LOGIN_INFO);

    QVariantList varList;
    varList << secretId;

    QSqlQuery query = m_db.exec(sql,varList);
    return query.next(); //是否有数据
}

void DaoLoginInfoSqlite::insert(const LoginInfo& info)
{
    QString sql = QString(
                      "insert into %1 (name, secret_id, secret_key, remark, timestamp) "
                      "values (?, ?, ?, ?, ?)").arg(CONFIG::TABLES::LOGIN_INFO);
    QVariantList varList;
    varList << info.name
            << info.secretId
            << info.secretKey
            << info.remark
            << info.timestamp;
    m_db.exec(sql, varList);
}

void DaoLoginInfoSqlite::remove(const QString& secretId)
{
    QString sql = QString(
                      "delete from %1 where  "
                      "secret_id = ?")
                      .arg(CONFIG::TABLES::LOGIN_INFO);
    QVariantList varList;
    varList << secretId;
    m_db.exec(sql, varList);
}

void DaoLoginInfoSqlite::update(const LoginInfo& info)
{
    QString sql = QString(
                      "update %1 "
                      "set name=?, "
                      "secret_key=?, "
                      "remark=?, "
                      "timestamp=? "
                      "where secret_id = ?")
                      .arg(CONFIG::TABLES::LOGIN_INFO);
    QVariantList varList;
    varList << info.name
            << info.secretKey
            << info.remark
            << info.timestamp
            << info.secretId;
    m_db.exec(sql, varList);
}

//void DaoLoginInfoSqlite::insert(const LoginInfo& info)
//{
//    QString sql = QString(
//                      "insert into %1 (name, secret_id, secret_key, remark, timestamp) "
//                      "values ('%2','%3', '%4', '%5', %6)")
//                      .arg(CONFIG::TABLES::LOGIN_INFO,info.name,info.secretId,info.secretKey,info.remark)
//                      .arg(info.timestamp);
//    m_db.exec(sql);

//}

//void DaoLoginInfoSqlite::remove(const QString& secretId)
//{
//    QString sql = QString(
//                      "delete from %1 where  "
//                      "secret_id = '%2';")
//                      .arg(CONFIG::TABLES::LOGIN_INFO,secretId);
//    m_db.exec(sql);
//}

//void DaoLoginInfoSqlite::update(const LoginInfo& info)
//{
//    QString sql = QString(
//                      "update %1 "
//                      "set name='%2', "
//                      "secret_key='%3', "
//                      "remark='%4', "
//                      "timestamp=%5 "
//                      "where secret_id='%6'")
//                      .arg(CONFIG::TABLES::LOGIN_INFO,info.name,info.secretKey,info.remark)
//                      .arg(info.timestamp)
//                      .arg(info.secretId);
//    m_db.exec(sql);
//}

QList<LoginInfo> DaoLoginInfoSqlite::select()
{
    QList<LoginInfo> retList;
    QString sql = QString("select name, secret_id, secret_key, remark from %1 "
                        "order by timestamp desc;")
                        .arg(CONFIG::TABLES::LOGIN_INFO);
    QList<RECORD> recordList = m_db.select(sql);
    for(const RECORD& record: recordList)
    {
        LoginInfo info;
        info.name = record["name"].toString();
        info.secretId = record["secret_id"].toString();
        info.secretKey = record["secret_key"].toString();
        info.remark = record["remark"].toString();
        retList.append(info);
    }
    return retList;
}
