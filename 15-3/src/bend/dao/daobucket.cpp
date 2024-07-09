#include "daobucket.h"

#include "src/helper/filehelper.h"

#include <QJsonArray>
#include <QDebug>

DaoBucket::DaoBucket()
{

}

QList<MyBucket> DaoBucket::bucketsFromMock(const QString &path)
{
    QList<MyBucket> buckets;
    QVariant variant = FileHelper::readAllJson(path);
    QJsonArray arr = variant.toJsonArray();
    for(int i=0; i< arr.count(); i++)
    {
        QJsonValue v = arr[i];

        MyBucket bucket;
        bucket.name=v["name"].toString();
        bucket.location=v["location"].toString();
        bucket.createDate=v["create_date"].toString();
        qDebug() << bucket.name << bucket.location << bucket.createDate;

        buckets.append(bucket);
    }
    return buckets;
}
