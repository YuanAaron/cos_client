#ifndef DAOCLOUDSCOS_H
#define DAOCLOUDSCOS_H

#include "DaoClouds.h"
#include <QList>

namespace qcloud_cos {
class CosConfig;
class CosResult;
class GetBucketResp;
}

class DaoCloudsCos : public DaoClouds
{
public:
    DaoCloudsCos();
    ~DaoCloudsCos();

    virtual QList<MyBucket> buckets() override;
    virtual bool isBucketExists(const QString &bucketName) override;
    virtual QString getBucketLocation(const QString &bucketName) override;
    virtual void putBucket(const QString &bucketName, const QString &location) override;
    virtual void deleteBucket(const QString &bucketName) override;

    virtual QList<MyObject> getObjects(const QString& bucketName, const QString& dir) override;

    virtual QList<MyBucket> login(const QString &secretId, const QString &secretKey) override;

private:
    void throwError(const QString& code, qcloud_cos::CosResult& result);

    QList<MyObject> getDirList(qcloud_cos::GetBucketResp& resp, const QString& dir);
    QList<MyObject> getFileList(qcloud_cos::GetBucketResp& resp, const QString& dir);

private:
    qcloud_cos::CosConfig* m_config = nullptr;
};

#endif // DAOCLOUDSCOS_H
