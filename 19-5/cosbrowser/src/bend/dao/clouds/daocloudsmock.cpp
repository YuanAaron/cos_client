#include "daocloudsmock.h"

#include <src/helper/filehelper.h>

#include <QJsonArray>

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

        buckets.append(bucket);
    }
    return buckets;
}
