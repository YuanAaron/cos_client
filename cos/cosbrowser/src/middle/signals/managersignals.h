#ifndef MANAGERSIGNALS_H
#define MANAGERSIGNALS_H

#include <QObject>

#include <src/middle/models/mybucket.h>

class ManagerSignals : public QObject
{
    Q_OBJECT
public:
    explicit ManagerSignals(QObject *parent = nullptr);
    ~ManagerSignals();

signals:
    void loginSuccess();
    void error(int api, const QString& msg);
    void unLogin();

    void bucketsSuccess(const QList<MyBucket>& buckets);

};

#endif // MANAGERSIGNALS_H
