#include "src\fend\uimain\uimain.h"
#include <src/fend/uilogin/logindialog.h>
#include "src/middle/managerglobal.h"

#include <QApplication>
#include <QDebug>

#include <src/fend/uicommon/pagewidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MG->init(argc,argv);

    //用户登录窗口和主窗口切换的需求：
    //登录
        //成功 进入主界面
        //失败 弹出提示信息
    //退出登录 显示登录界面
    UiMain w;
    LoginDialog login;
    login.show();

//    PageWidget w;
//    w.setMaxRowList(QList<int>() << 10 << 50 << 100);
//    w.setTotalRow(330);
//    w.show();

    return a.exec();
}
