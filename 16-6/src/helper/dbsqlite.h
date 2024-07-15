#ifndef DBSQLITE_H
#define DBSQLITE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariantList>

#include <src/bend/models/logininfo.h>
#include <QMap>

typedef QMap<QString, QVariant> RECORD;

class DBSqlite
{
public:
    DBSqlite();
    ~DBSqlite();

    void connect(const QString& DBPath);
    QSqlQuery exec(const QString& sql);
    QSqlQuery exec(const QString& sql, const QVariantList& variantList);

    bool exists(const QString& secretId);

    QList<RECORD> select(const QString& sql);

private:
    QSqlDatabase m_db;
};

#endif // DBSQLITE_H
