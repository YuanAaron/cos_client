#ifndef DBMODELS_H
#define DBMODELS_H

#include <QString>

struct LoginInfo
{
    QString name;
    QString secretId;
    QString secretKey;
    QString remark;
    uint timestamp;
};

#endif // DBMODELS_H
