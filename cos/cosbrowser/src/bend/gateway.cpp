#include "gateway.h"

#include "src/config/loggerproxy.h"
#include "src/config/api.h"
#include "src/bend/manager/managercloud.h"
#include "src/middle/managerglobal.h"
#include "src/middle/signals/managersignals.h"
#include <QtConcurrent>
#include <src/config/exceptions.h>
#include <src/config/errorcode.h>

GateWay::GateWay(QObject *parent) : QObject(parent)
{

}

GateWay::~GateWay()
{
    qDebug("delete GateWay");
}

void GateWay::send(int api, const QJsonValue &params)
{
    QtConcurrent::run([=](){
        try {
            this->dispatch(api,params);
        } catch (BaseException e) {
            mError(e.msg());
            emit MG->m_signal->error(api,e.msg(), params);
        } catch(...){
            BaseException e = BaseException(EC_100000,QString::fromLocal8Bit("未知错误"));
            mError(e.msg());
            emit MG->m_signal->error(api, e.msg(), params);
        }
    });
}

void GateWay::dispatch(int api, const QJsonValue &params)
{
    //查询路由表
    switch(api)
    {
    case API::LOGIN::NORMAL:
        apiLogin(params);
        break;

    //桶操作接口
    case API::BUCKETS::LIST:
        apiGetBuckets(params);
        break;
    case API::BUCKETS::PUT:
        apiPutBucket(params);
        break;
    case API::BUCKETS::DEL:
        apiDeleteBucket(params);
        break;

    //对象操作接口
    case API::OBJECTS::LIST:
        apiGetObjects(params);
        break;
    case API::OBJECTS::GET:
        apiGetObject(params);
        break;
    case API::OBJECTS::PUT:
        apiPutObject(params);
        break;
    default:
        break;
    }
}

void GateWay::apiLogin(const QJsonValue &value)
{
    QString secretId = value["secretId"].toString();
    QString secretKey = value["secretKey"].toString();
    MG->m_cloud->login(secretId, secretKey);
}

void GateWay::apiGetBuckets(const QJsonValue &params)
{
    MG->m_cloud->getBuckets();
}

void GateWay::apiPutBucket(const QJsonValue &params)
{
    QString bucketName = params["bucketName"].toString();
    QString location = params["location"].toString();
    MG->m_cloud->putBucket(bucketName, location);
}

void GateWay::apiDeleteBucket(const QJsonValue &params)
{
    QString bucketName = params["bucketName"].toString();
    MG->m_cloud->deleteBucket(bucketName);
}

void GateWay::apiGetObjects(const QJsonValue &params)
{
    QString bucketName = params["bucketName"].toString();
    QString dir = params["dir"].toString();
    MG->m_cloud->getObjects(bucketName, dir);
}

void GateWay::apiGetObject(const QJsonValue &params)
{
    QString jobId = params["jobId"].toString(); //用于更新下载进度的任务id
    QString bucketName = params["bucketName"].toString();
    QString key = params["key"].toString();
    QString localPath = params["localPath"].toString();
    MG->m_cloud->getObject(jobId, bucketName, key, localPath);
}

void GateWay::apiPutObject(const QJsonValue &params)
{
    QString jobId = params["jobId"].toString(); //用于更新上传进度的任务id
    QString bucketName = params["bucketName"].toString();
    QString key = params["key"].toString();
    QString localPath = params["localPath"].toString();
    MG->m_cloud->putObjcet(jobId, bucketName, key, localPath);
}
