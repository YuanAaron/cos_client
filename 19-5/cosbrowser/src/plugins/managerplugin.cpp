#include "managerplugin.h"

#include <src/bend/dao/clouds/daocloudsmock.h>
#include <src/bend/dao/config/versionjson.h>
#include "src/config/global.h"
using namespace GLOBAL;

Q_GLOBAL_STATIC(ManagerPlugin, ins)

ManagerPlugin::ManagerPlugin(QObject *parent) : QObject(parent)
{

}

ManagerPlugin::~ManagerPlugin()
{
    delete m_clouds;
    delete m_version;
}

ManagerPlugin *ManagerPlugin::instance()
{
    return ins();
}

void ManagerPlugin::installPlugins()
{
    m_version = new VersionJson(VERSION::JSON_PATH);
    m_version->setVersion();
    if(m_version->major() == VERSION::MAJOR_BUSINESS)
    {
        m_clouds = new DaoCloudsMock(":/static/test/business.json");
    }
    else
    {
        m_clouds = new DaoCloudsMock(":/static/test/custom.json");
    }

}

DaoClouds *ManagerPlugin::clouds() const
{
    return m_clouds;
}
