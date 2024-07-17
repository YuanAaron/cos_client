#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>
#include <QThread>

class UserManager : public QObject
{
    Q_OBJECT
public:
    explicit UserManager(QObject *parent = nullptr);
    ~UserManager();

signals:
    void searchBasicFinished(const QString& name);
    void searchJobFinished(const QString& name);

public slots:
    void onSearchBasic();
    void onSearchJob();

private:
    QThread* td;

};

#endif // USERMANAGER_H
