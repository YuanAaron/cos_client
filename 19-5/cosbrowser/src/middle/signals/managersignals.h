#ifndef MANAGERSIGNALS_H
#define MANAGERSIGNALS_H

#include <QObject>

#define MS ManagerSignals::instance()

class ManagerSignals : public QObject
{
    Q_OBJECT
public:
    explicit ManagerSignals(QObject *parent = nullptr);
    static ManagerSignals* instance();

signals:
    void loginSuccess();
    void error(int api, const QString& msg);
    void unLogin();

};

#endif // MANAGERSIGNALS_H
