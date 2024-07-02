#include "logindialog.h"

#include <QApplication>
#include <QWidget>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //需求：点击登录后，弹出主窗口；点击关闭，退出当前应用程序
    LoginDialog w;
//    w.show();

    QWidget m;
    m.setWindowTitle(QString::fromLocal8Bit("主窗口"));

    //将登录窗口设置为模态窗口（程序会阻塞）：使用exec显示登录窗口
    int code = w.exec();
    //用户点击了登录还是关闭，code会有不同的返回值（需要设置 点击登录按钮调用accept()槽函数，点击关闭按钮调用reject()槽函数）
    if(code == QDialog::Accepted)
    {
        m.show();
        return a.exec();
    }
    else
    {
        qDebug() << QString::fromLocal8Bit("退出程序");
    }
}
