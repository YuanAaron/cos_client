#ifndef DAOCLOUDSCOS_H
#define DAOCLOUDSCOS_H

#include "DaoClouds.h"
#include <QList>

namespace qcloud_cos {
class CosConfig;
}

class DaoCloudsCos : public DaoClouds
{
public:
    DaoCloudsCos();
    ~DaoCloudsCos();

    virtual QList<MyBucket> buckets() override;
    virtual QList<MyBucket> login(const QString &secretId, const QString &secretKey) override;

private:
    qcloud_cos::CosConfig* m_config = nullptr;
};

#endif // DAOCLOUDSCOS_H
