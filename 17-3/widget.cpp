#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnStartSearch_clicked()
{
    ui->textEdit->append(QString::fromLocal8Bit("开始查询数据库..."));
    if(!mth)
    {
        mth = new MyThread();
        connect(mth, &MyThread::finished, this, &Widget::onFinished);
    }
    if(!mth->isRunning())
    {
        mth->start();
    }
}

void Widget::onFinished()
{
    ui->textEdit->append(QString::fromLocal8Bit("查询数据完成"));
}

void Widget::on_btnStopSearch_clicked()
{
    if(mth)
    {
        mth->stop();
    }
    qDebug() << QString::fromLocal8Bit("stop中调用的wait导致主线程被阻塞");
}
