﻿#ifndef GATEWAY_H
#define GATEWAY_H

#include <QJsonValue>
#include <QObject>

class GateWay : public QObject
{
    Q_OBJECT
public:
    explicit GateWay(QObject *parent = nullptr);
    ~GateWay();

    void send(int api, const QJsonValue& params = QJsonValue());

private:
    void dispatch(int api, const QJsonValue& value);
    void apiLogin(const QJsonValue& params);

    //桶操作接口
    void apiGetBuckets(const QJsonValue& params);
    void apiPutBucket(const QJsonValue& params);
    void apiDeleteBucket(const QJsonValue& params);

    //对象操作接口
    void apiGetObjects(const QJsonValue& params);
    void apiGetObject(const QJsonValue& params);
    void apiPutObject(const QJsonValue& params);

};

#endif // GATEWAY_H
