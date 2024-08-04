#ifndef DAOCLOUDSMOCK_H
#define DAOCLOUDSMOCK_H

#include "DaoClouds.h"
#include <QJsonValue>

class DaoCloudsMock : public DaoClouds
{
public:
    DaoCloudsMock(const QString& path);

    virtual QList<MyBucket> buckets() override;
    virtual bool isBucketExists(const QString &bucketName) override;
    virtual QString getBucketLocation(const QString &bucketName) override;
    virtual void putBucket(const QString &bucketName, const QString &location) override;
    virtual void deleteBucket(const QString &bucketName) override;

    virtual QList<MyObject> getObjects(const QString& bucketName, const QString& dir) override;

    virtual QList<MyBucket> login(const QString &secretId, const QString &secretKey) override;

private:
    QJsonValue m_mock;
};

#endif // DAOCLOUDSMOCK_H
