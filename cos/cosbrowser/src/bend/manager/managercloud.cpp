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
    emit MG->m_signal->loginSuccess();
    bucketsAlready(buckets);
}

void ManagerCloud::getBuckets()
{
    QList<MyBucket> buckets = MG->m_plugin->clouds()->buckets();
    bucketsAlready(buckets);
}

void ManagerCloud::putBucket(const QString &bucketName, const QString &location)
{
    MG->m_plugin->clouds()->putBucket(bucketName,location);
    getBuckets();
}

void ManagerCloud::deleteBucket(const QString &bucketName)
{
    MG->m_plugin->clouds()->deleteBucket(bucketName);
    getBuckets();
}

void ManagerCloud::getObjects(const QString &bucketName, const QString &dir)
{
    QList<MyObject> objs = MG->m_plugin->clouds()->getObjects(bucketName, dir);
    m_currentBucketName = bucketName;
    m_currentDir = dir;
    emit MG->m_signal->objectsSuccess(objs);
}

void ManagerCloud::getObject(const QString &jobId, const QString &bucketName, const QString &key, const QString &localPath)
{
    auto callback = [=](qulonglong transferred_size, qulonglong total_size, void *){
        assert(transferred_size < total_size);
        if(0 == transferred_size % (1024 * 1024))
        {
            emit MG->m_signal->downloadProcess(jobId, transferred_size, total_size);
        }
    };
    MG->m_plugin->clouds()->getObject(bucketName, key, localPath, callback);
    emit MG->m_signal->downloadSuccess(jobId);
}

void ManagerCloud::putObjcet(const QString &jobId, const QString &bucketName, const QString &key, const QString &localPath)
{
    auto callback = [=](qulonglong transferred_size, qulonglong total_size, void *){
        assert(transferred_size <= total_size);
        if(0 == transferred_size % (1024 * 1024))
        {
            emit MG->m_signal->uploadProcess(jobId, transferred_size, total_size);
        }
    };
    MG->m_plugin->clouds()->putObject(bucketName, key, localPath, callback);
    emit MG->m_signal->uploadSuccess(jobId);
}

void ManagerCloud::bucketsAlready(const QList<MyBucket> &buckets)
{
    m_currentBucketName.clear();
    m_currentDir.clear();
    emit MG->m_signal->bucketsSuccess(buckets);
}

QString ManagerCloud::getCurrentDir() const
{
    return m_currentDir;
}

QString ManagerCloud::getCurrentBucketName() const
{
    return m_currentBucketName;
}
