#include "src\fend\uimain\uimain.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //用户登录窗口和主窗口切换的需求：
    //登录
        //成功 进入主界面
        //失败 弹出提示信息
    //退出登录 显示登录界面
    UiMain w;
    w.show();
//    w.showLoginDialog();
    return a.exec();
}
