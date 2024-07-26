#ifndef MANAGERSIGNALS_H
#define MANAGERSIGNALS_H

#include <QObject>

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

};

#endif // MANAGERSIGNALS_H
