#ifndef DAOLOGININFO_H
#define DAOLOGININFO_H

#include <src/middle/models/logininfo.h>

class DaoLoginInfo
{
public:
    virtual void connect() = 0;
    virtual void createLoginInfoTable() = 0;

    virtual bool exists(const QString& secretId) = 0;
    virtual void insert(const LoginInfo& info) = 0;
    virtual void remove(const QString& secretId) = 0;
    virtual void update(const LoginInfo& info) = 0;

    virtual QList<LoginInfo> select() = 0;
};

#endif // DAOLOGININFO_H
