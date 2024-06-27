#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SIGNAL(numChanged(int)));
    connect(this, SIGNAL(numChanged(int)), this, SLOT(onNumChanged(int)));

    //疑问：按钮点击信号和槽是自动绑定的？？？
    //连接打印引号和槽
    //connect(this, SIGNAL(printLog(int)), this, SLOT(onPrintLog(int)));
    connect(this, &Widget::printLog, this, &Widget::onPrintLog);
}

Widget::~Widget()
{
    delete ui;
}

//void Widget::onSpinBoxValueChanged(int val)
//{
//    qDebug()<<"onSpinBoxValueChanged";
//    emit numChanged(val);
//}

void Widget::onNumChanged(int val)
{
    qDebug("onNumChanged");
    ui->progressBar->setValue(val);
}


void Widget::on_pushButton_clicked()
{
    emit printLog(1);
}

void Widget::onPrintLog(int a)
{
    qDebug() << "onPrintLog";
}
