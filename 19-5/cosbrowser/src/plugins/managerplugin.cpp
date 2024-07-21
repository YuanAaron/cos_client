#include "managerplugin.h"

#include <src/bend/dao/clouds/daocloudsmock.h>

Q_GLOBAL_STATIC(ManagerPlugin, ins)

ManagerPlugin::ManagerPlugin(QObject *parent) : QObject(parent)
{
    installPlugins();
}

ManagerPlugin *ManagerPlugin::instance()
{
    return ins();
}

void ManagerPlugin::installPlugins()
{
    m_clouds = new DaoCloudsMock(":/static/test/buckets1.json");
}

DaoClouds *ManagerPlugin::clouds() const
{
    return m_clouds;
}
