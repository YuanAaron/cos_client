﻿#include "src\fend\uimain\uimain.h"
#include "src\helper\filehelper.h"

#include <src/bend/manager/managercloud.h>
#include <src/bend/manager/managerdb.h>

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Mock测试
//    DaoBucket buckets;
//    buckets.bucketsFromMock(":/static/test/buckets2.json");

    //QSS美化登录窗口
    //1.读取文件中的qss
//    QString qss = FileHelper::readAllTxt("C:/Users/oshacker/Desktop/qtlessons/12/12-5/static/qss/default.qss");
    QString qss = FileHelper::readAllTxt(":/static/qss/default.qss");
    //2.QApplication加载qss
    a.setStyleSheet(qss);

    //数据库
    MDB->init();

    //用户登录窗口和主窗口切换的需求：
    //登录
        //成功 进入主界面
        //失败 弹出提示信息
    //退出登录 显示登录界面
    UiMain w;
//    w.show();
    w.showLoginDialog();

    MC->print();
    MC->print();

    MC->setBucket();

    qDebug() << QString::fromLocal8Bit("无意中发现了bug: uimain.h中的m_loginDialog必须设为nullptr");
    return a.exec();
}
