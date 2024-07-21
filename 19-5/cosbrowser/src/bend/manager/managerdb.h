#ifndef MANAGERDB_H
#define MANAGERDB_H

#include <QObject>

#include <src/middle/models/logininfo.h>

#include <src/bend/dao/dbs/daologininfosqlite.h>

#define MDB ManagerDB::instance()

class ManagerDB : public QObject
{
    Q_OBJECT
public:
    explicit ManagerDB(QObject *parent = nullptr);

    static ManagerDB* instance();

    void init();

    void saveLoginInfo(const QString& name, const QString& id, const QString& key, const QString remark);
    void removeLoginInfo(const QString& id);
    int indexOfLoginInfo(const QString& secretId);

    QStringList loginNameList();
    LoginInfo loginInfoByName(const QString& name);
signals:

private:
    DaoLoginInfoSqlite m_daoLoginInfo;
    QList<LoginInfo> m_loginInfoList; //缓存
};

#endif // MANAGERDB_H
