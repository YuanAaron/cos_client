#include "src\fend\uimain\uimain.h"
#include <src/fend/uilogin/logindialog.h>
#include "src/middle/managerglobal.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "zhangsan";

    MG->init(argc,argv);

    //用户登录窗口和主窗口切换的需求：
    //登录
        //成功 进入主界面
        //失败 弹出提示信息
    //退出登录 显示登录界面
    UiMain w;
    LoginDialog login;
    login.updateLoginInfo();
    login.show();

    return a.exec();
}
