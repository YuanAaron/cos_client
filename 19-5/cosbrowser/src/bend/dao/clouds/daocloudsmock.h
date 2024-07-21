#ifndef DAOCLOUDSMOCK_H
#define DAOCLOUDSMOCK_H

#include "DaoClouds.h"
#include <QJsonValue>

class DaoCloudsMock : public DaoClouds
{
public:
    DaoCloudsMock(const QString& path);

    virtual QList<MyBucket> buckets() override;

private:
    QJsonValue m_mock;
};

#endif // DAOCLOUDSMOCK_H
