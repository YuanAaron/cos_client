#include "managercloud.h"

#include <QDebug>

#include <src/middle/models/cloudmodels.h>
#include <src/plugins/managerplugin.h>
#include "src/middle/signals/managersignals.h"
#include "src/middle/managerglobal.h"

ManagerCloud::ManagerCloud(QObject *parent) : QObject(parent)
{

}

ManagerCloud::~ManagerCloud()
{
    qDebug() << "delete ManagerCloud ";
}

void ManagerCloud::login(QString secretId, QString secretKey)
{
    QList<MyBucket> buckets = MG->m_plugin->clouds()->login(secretId, secretKey);
    emit MG->m_signal->bucketsSuccess(buckets);
}
