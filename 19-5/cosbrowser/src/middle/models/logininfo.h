#ifndef LOGININFO_H
#define LOGININFO_H

#include <QString>

struct LoginInfo
{
    QString name;
    QString secretId;
    QString secretKey;
    QString remark;
    uint timestamp;
};

#endif // LOGININFO_H
