#ifndef DAOLOGININFOSQLITE_H
#define DAOLOGININFOSQLITE_H

#include "daologininfo.h"

#include <src/helper/dbsqlite.h>

class DaoLoginInfoSqlite : public DaoLoginInfo
{
public:
    DaoLoginInfoSqlite();

    virtual void connect() override;
    virtual void createLoginInfoTable() override;

    virtual bool exists(const QString& secretId) override;
    virtual void insert(const LoginInfo& info) override;
    virtual void remove(const QString& secretId) override;
    virtual void update(const LoginInfo& info) override;

    virtual QList<LoginInfo> select() override;

private:
    DBSqlite m_db;
};

#endif // DAOLOGININFOSQLITE_H
