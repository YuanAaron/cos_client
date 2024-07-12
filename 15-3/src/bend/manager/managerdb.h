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
signals:

private:
    DaoLoginInfo m_daoLoginInfo;
};

#endif // MANAGERDB_H
