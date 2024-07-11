#ifndef DBSQLITE_H
#define DBSQLITE_H

#include <QString>
#include <QSqlDatabase>

class DBSqlite
{
public:
    DBSqlite();
    ~DBSqlite();

    void connect(const QString& DBPath);
    void exec(const QString& sql);

private:
    QSqlDatabase m_db;
};

#endif // DBSQLITE_H
