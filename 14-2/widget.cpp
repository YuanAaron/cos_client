#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QThread>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(this, SIGNAL(downloadFile()), this, SLOT(onDownloadFile2()));
    connect(this, SIGNAL(downloadFile()), this, SLOT(onDownloadFile3()));
    connect(this, SIGNAL(downloadFile()), this, SLOT(onDownloadFile1()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::renameFile()
{
    qDebug("renameFile");
}


void Widget::on_pushButton_clicked()
{
    //单线程
    //1、信号发出后，先执行槽函数，在执行信号后面的函数
    //2、信号与多个槽函数连接，槽函数按照connect连接的顺序执行
    //3、综合上面两条的顺序进行执行
    emit downloadFile();
    //4. 原理：信号槽只是在代码编写形式上进行了分离，而实质上仍然按顺序调用函数。
//    onDownloadFile2();
//    onDownloadFile3();
//    onDownloadFile1();
    renameFile();
}

void Widget::onDownloadFile1()
{
    qDebug("onDownloadFile1 start");
    thread()->sleep(1);
    qDebug("onDownloadFile1 finish");
}

void Widget::onDownloadFile2()
{
    qDebug("onDownloadFile2 start");
    thread()->sleep(1);
    qDebug("onDownloadFile2 finish");
}

void Widget::onDownloadFile3()
{
    qDebug("onDownloadFile3 start");
    thread()->sleep(1);
    qDebug("onDownloadFile3 finish");
}
