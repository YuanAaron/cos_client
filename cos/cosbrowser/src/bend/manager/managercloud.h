#ifndef MANAGERBUCKET_H
#define MANAGERBUCKET_H

#include <QObject>
#include <src/middle/models/cloudmodels.h>

class ManagerCloud : public QObject
{
    Q_OBJECT
public:
    //不要直接构造函数创建对象，直接使用instance来使用对象即可
    explicit ManagerCloud(QObject *parent = nullptr);
    ~ManagerCloud();

    void login(QString secretId, QString secretKey);

    // 桶操作接口
    void getBuckets();
    void putBucket(const QString& bucketName, const QString& location);
    void deleteBucket(const QString& bucketName);

    // 对象操作接口
    void getObjects(const QString& bucketName, const QString& dir = "");
    void getObject(const QString& jobId,
                   const QString& bucketName,
                   const QString& key,
                   const QString& localPath);
    void putObjcet(const QString& jobId,
                   const QString& bucketName,
                   const QString& key,
                   const QString& localPath);

    QString getCurrentBucketName() const;
    QString getCurrentDir() const;

private:
    void bucketsAlready(const QList<MyBucket>& buckets);

private:
    QString m_currentBucketName; //记录当前对象所在的存储桶名
    QString m_currentDir; //记录当前对象所在的父目录

};

#endif // MANAGERBUCKET_H
