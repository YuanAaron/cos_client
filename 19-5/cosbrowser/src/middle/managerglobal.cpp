#include "managerglobal.h"
#include "managermodel.h"

#include <src/bend/manager/managercloud.h>
#include <src/bend/manager/managerdb.h>
#include <src/plugins/managerplugin.h>
#include <src/config/loggerproxy.h>
#include <src/bend/gateway.h>
#include <src/middle/signals/managersignals.h>
#include <QApplication>

Q_GLOBAL_STATIC(ManagerGlobal,ins)

ManagerGlobal::ManagerGlobal(QObject *parent) : QObject(parent)
{
    //使用对象树所属关系系统进行内存释放
    m_cloud = new ManagerCloud(this);
    m_db = new ManagerDB(this);
    m_plugin = new ManagerPlugin(this);
    m_log = new LoggerProxy(this);
    m_gate = new GateWay(this);
    m_signal = new ManagerSignals(this);
//    m_model = new ManagerModel(this); //TODO 为啥放在这里程序启动不起来，放在init方法中OK
}

ManagerGlobal::~ManagerGlobal()
{
    qDebug("delete ManagerGlobal");
}

ManagerGlobal *ManagerGlobal::instance()
{
    return ins();
}

void ManagerGlobal::init(int argc, char* argv[])
{
    m_model = new ManagerModel(this);

    FileHelper::mkPath(GLOBAL::PATH::LOG_DIR);
    FileHelper::mkPath(GLOBAL::PATH::TMP);

    m_plugin->installPlugins(argc, argv);

    //QSS美化登录窗口
    //1.读取文件中的qss
//    QString qss = FileHelper::readAllTxt("C:/Users/oshacker/Desktop/qtlessons/12/12-5/static/qss/default.qss");
    QString qss = FileHelper::readAllTxt(":/static/qss/default.qss");
    //2.QApplication加载qss
//    a.setStyleSheet(qss);
    qApp->setStyleSheet(qss); //qApp是一个单例

    //数据库
    m_db->init();
}
