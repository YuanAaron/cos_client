#ifndef GATEWAY_H
#define GATEWAY_H

#include <QJsonValue>
#include <QObject>

class GateWay : public QObject
{
    Q_OBJECT
public:
    explicit GateWay(QObject *parent = nullptr);
    ~GateWay();

    void send(int api, const QJsonValue& value);

private:
    void dispatch(int api, const QJsonValue& value);
    void apiLogin(const QJsonValue& value);
};

#endif // GATEWAY_H
