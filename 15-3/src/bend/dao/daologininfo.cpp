﻿#include "daologininfo.h"
#include "src/config/config.h"

DaoLoginInfo::DaoLoginInfo()
{

}

void DaoLoginInfo::connect()
{
    m_db.connect(CONFIG::SQLITE::NAME);
}

void DaoLoginInfo::createLoginInfoTable()
{
    QString sql = FileHelper::readAllTxt(CONFIG::SQL::LOGIN_INFO_TABLE);
    m_db.exec(sql);
}

bool DaoLoginInfo::exists(const QString &secretId)
{
    QString sql = QString(
                      "select id from %1 where  "
                      "secret_id = '%2';")
                      .arg(CONFIG::TABLES::LOGIN_INFO, secretId);
    return m_db.exists(sql);
}

void DaoLoginInfo::insert(const LoginInfo& info)
{
    QString sql = QString(
                      "insert into %1 (name, secret_id, secret_key, remark, timestamp) "
                      "values (%2, %3, %4, %5, %6)")
                      .arg(CONFIG::TABLES::LOGIN_INFO,info.name,info.secretId,info.secretKey,info.remark)
                      .arg(info.timestamp); //arg最多5个参数
    m_db.exec(sql);

}

void DaoLoginInfo::remove(const QString& secretId)
{
    QString sql = QString(
                      "delete from %1 where  "
                      "secret_id = %2;")
                      .arg(CONFIG::TABLES::LOGIN_INFO,secretId);
    m_db.exec(sql);
}

void DaoLoginInfo::update(const LoginInfo& info)
{
    QString sql = QString(
                      "update %1 "
                      "set name=%2, "
                      "secret_key=%3, "
                      "remark=%4, "
                      "timestamp=%5 "
                      "where secret_id %6 ?")
                      .arg(CONFIG::TABLES::LOGIN_INFO, info.name,info.secretKey,info.remark)
                      .arg(info.secretId);
    m_db.exec(sql);
}
