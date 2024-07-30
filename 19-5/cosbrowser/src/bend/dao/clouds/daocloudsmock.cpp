#include "daocloudsmock.h"

#include <src/config/exceptions.h>
#include <src/helper/filehelper.h>
#include <src/middle/managerglobal.h>
#include "src/config/errorcode.h"

#include <QJsonArray>
#include <QThread>

DaoCloudsMock::DaoCloudsMock(const QString& path)
{
    m_mock = FileHelper::readAllJson(path).toJsonValue();
}

QList<MyBucket> DaoCloudsMock::buckets()
{
    QList<MyBucket> buckets;
    QJsonArray arr = m_mock["buckets"].toArray();
    for(int i=0; i< arr.count(); i++)
    {
        QJsonValue v = arr[i];

        MyBucket bucket;
        bucket.name=v["name"].toString();
        bucket.location=v["location"].toString();
        bucket.createDate=v["create_date"].toString();
//        qDebug() << bucket.name << bucket.location << bucket.createDate;
        mInfo(QString::fromLocal8Bit("name[%1], location[%2], date[%3]").arg(bucket.name,bucket.location, bucket.createDate));

        buckets.append(bucket);
    }
    return buckets;
}

QList<MyBucket> DaoCloudsMock::login(const QString &secretId, const QString &secretKey)
{
    QThread::sleep(3);
    QJsonArray arr = m_mock["users"].toArray();
    for(int i=0; i<arr.count(); i++)
    {
        QJsonValue v = arr[i];
        if(secretId == v["secretId"].toString() && secretKey == v["secretKey"].toString())
        {
            return buckets();
        }
    }
    throw BaseException(EC_211000,QString::fromLocal8Bit("请检查您的SecretId或SecretKey是否正确"));
}
