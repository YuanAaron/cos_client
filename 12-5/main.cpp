#include "src\fend\uimain\uimain.h"
#include "src\helper\filehelper.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QSS美化登录窗口
    //1.读取文件中的qss
//    QString qss = FileHelper::readAllTxt("C:/Users/oshacker/Desktop/qtlessons/12/12-5/static/qss/default.qss");
    QString qss = FileHelper::readAllTxt(":/static/qss/default.qss");

    //2.QApplication加载qss
    a.setStyleSheet(qss);

    //用户登录窗口和主窗口切换的需求：
    //登录
        //成功 进入主界面
        //失败 弹出提示信息
    //退出登录 显示登录界面
    UiMain w;
//    w.show();
    w.showLoginDialog();
    return a.exec();
}
