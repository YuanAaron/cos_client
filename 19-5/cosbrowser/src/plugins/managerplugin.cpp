#include "managerplugin.h"

#include <src/bend/dao/clouds/daocloudsmock.h>
#include <src/bend/dao/config/versioncmd.h>
#include <src/bend/dao/config/versionjson.h>
#include <src/bend/dao/logs/loggerqdebug.h>
#include "src/config/global.h"
#include "src/config/loggerproxy.h"
#include "src/middle/managerglobal.h"
using namespace GLOBAL;

ManagerPlugin::ManagerPlugin(QObject *parent) : QObject(parent)
{

}

ManagerPlugin::~ManagerPlugin()
{
    qDebug("delete ManagerPlugin");
    delete m_clouds;
    delete m_version;
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
    MG->m_log->setLogger(new LoggerQDebug());
//    MG->m_log->setLevel(LOG_LEVEL::INFO);
}

DaoClouds *ManagerPlugin::clouds() const
{
    return m_clouds;
}
