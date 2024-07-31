#ifndef DAOCLOUDSCOS_H
#define DAOCLOUDSCOS_H

#include "DaoClouds.h"
#include <QList>

class DaoCloudsCos : public DaoClouds
{
public:
    DaoCloudsCos();

    virtual QList<MyBucket> buckets() override;
    virtual QList<MyBucket> login(const QString &secretId, const QString &secretKey) override;
};

#endif // DAOCLOUDSCOS_H
