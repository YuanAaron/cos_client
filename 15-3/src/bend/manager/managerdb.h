#ifndef MANAGERDB_H
#define MANAGERDB_H

#include <QObject>

#include <src/bend/dao/daologininfo.h>

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
signals:

private:
    DaoLoginInfo m_daoLoginInfo;
};

#endif // MANAGERDB_H
