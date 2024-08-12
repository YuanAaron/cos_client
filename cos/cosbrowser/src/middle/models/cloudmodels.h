#ifndef CLOUDMODELS_H
#define CLOUDMODELS_H

#include <QString>
#include <QMetaType>

struct BaseObject{
    bool isValid() const{
        return !isInvalid();
    }
    bool isInvalid() const{
        return name.isNull() || name.isEmpty();
    }

    QString name;
};
Q_DECLARE_METATYPE(BaseObject); //没有好像也没问题

struct MyBucket: public BaseObject
{
    QString location;
    QString createDate;
};
Q_DECLARE_METATYPE(MyBucket); //没有好像也没问题

struct MyObject: public BaseObject
{
    bool isDir() const
    {
        return isValid() && name.endsWith("/");
    }
    bool isFile() const
    {
        return isValid() && !name.endsWith("/");
    }

    QString lastmodified;
    qulonglong size = 0;
    QString dir; //父对象路径（父目录），需要带/

    QString key;
};
Q_DECLARE_METATYPE(MyObject); //没有好像也没问题

#endif // CLOUDMODELS_H
