#ifndef MANAGERDB_H
#define MANAGERDB_H

#include <QObject>

#include <src/helper/dbsqlite.h>

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
    void connect();
    void createLoginInfoTable();
    DBSqlite m_db;

};

#endif // MANAGERDB_H
