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

void GateWay::send(int api, const QJsonValue &value)
{
    QtConcurrent::run([=](){
        try {
            this->dispatch(api,value);
        } catch (BaseException e) {
            mError(e.msg());
            emit MG->m_signal->error(api,e.msg());
        } catch(...){
            BaseException e = BaseException(EC_100000,QString::fromLocal8Bit("未知错误"));
            mError(e.msg());
            emit MG->m_signal->error(api, e.msg());
        }
    });
}

void GateWay::dispatch(int api, const QJsonValue &value)
{
    //查询路由表
    switch(api)
    {
    case API::LOGIN::NORMAL:
        apiLogin(value);
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
    emit MG->m_signal->loginSuccess();
}
