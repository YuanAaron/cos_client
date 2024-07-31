#ifndef MANAGERBUCKET_H
#define MANAGERBUCKET_H

#include <QObject>

class ManagerCloud : public QObject
{
    Q_OBJECT
public:
    //不要直接构造函数创建对象，直接使用instance来使用对象即可
    explicit ManagerCloud(QObject *parent = nullptr);
    ~ManagerCloud();

    void login(QString secretId, QString secretKey);
signals:

};

#endif // MANAGERBUCKET_H
