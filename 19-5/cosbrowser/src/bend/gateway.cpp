#include "gateway.h"

#include "src/config/loggerproxy.h"
#include "src/config/api.h"
#include "src/bend/manager/managercloud.h"
#include "src/middle/signals/managersignals.h"
#include <QtConcurrent>

Q_GLOBAL_STATIC(GateWay, ins)

GateWay::GateWay(QObject *parent) : QObject(parent)
{

}

GateWay *GateWay::instance()
{
    return ins();
}

void GateWay::send(int api, const QJsonValue &value)
{
    QtConcurrent::run([=](){
        try {
            this->dispatch(api,value);
        } catch (QString e) {
            mError(e);
            emit MS->error(api,e);
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
    MC->login(secretId, secretKey);
    emit MS->loginSuccess();
}
