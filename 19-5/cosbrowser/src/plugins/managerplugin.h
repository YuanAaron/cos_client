#ifndef MANAGERPLUGIN_H
#define MANAGERPLUGIN_H

#include <QObject>

#include <src/bend/dao/clouds/DaoClouds.h>

#define MP ManagerPlugin::instance()

class ManagerPlugin : public QObject
{
    Q_OBJECT
public:
    explicit ManagerPlugin(QObject *parent = nullptr);

    static ManagerPlugin *instance();

    DaoClouds* clouds() const;

signals:

private:
    void installPlugins();

private:
    DaoClouds* m_clouds;

};

#endif // MANAGERPLUGIN_H
