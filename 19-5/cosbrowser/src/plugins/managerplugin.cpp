#include "managerplugin.h"

#include <src/bend/dao/clouds/daocloudsmock.h>
#include <src/bend/dao/config/versioncmd.h>
#include <src/bend/dao/config/versionjson.h>
#include <src/bend/dao/logs/loggerqdebug.h>
#include "src/config/global.h"
#include "src/config/loggerproxy.h"
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

void ManagerPlugin::installPlugins(int argc, char* argv[])
{
    //如果输入命令行，则命令行参数的优先级更高，否则直接加载配置文件中的信息
    VersionCmd version(argc,argv);
    if(version.isValid())
    {
        m_version = new VersionCmd(argc,argv);
    }
    else
    {
        m_version = new VersionJson(VERSION::JSON_PATH);
    }

    m_version->setVersion();

    //安装云存储插件
    if(m_version->major() == VERSION::MAJOR_BUSINESS)
    {
        m_clouds = new DaoCloudsMock(":/static/test/business.json");
    }
    else
    {
        m_clouds = new DaoCloudsMock(":/static/test/custom.json");
    }

    //安装日志插件
    LOG->setLogger(new LoggerQDebug());
//    LOG->setLevel(LOG_LEVEL::INFO);
}

DaoClouds *ManagerPlugin::clouds() const
{
    return m_clouds;
}
