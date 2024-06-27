#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

//    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SIGNAL(numChanged(int)));
//    connect(this, SIGNAL(numChanged(int)), this, SLOT(onNumChanged(int)));

    //疑问：按钮点击信号和槽是自动绑定的？？？
    //连接打印引号和槽
    //connect(this, SIGNAL(printLog(int)), this, SLOT(onPrintLog(int)));
    //connect(this, &Widget::printLog, this, &Widget::onPrintLog);
//    connect(this, &Widget::printLog, this, [=](){
//        qDebug() << "onPrintLog";
//    });

    //connect(this, SIGNAL(printLog1(int)), this, SLOT(onPrintLog1(QString))); //编译没问题，运行报错
    //connect(this, &Widget::printLog1, this, &Widget::onPrintLog1); //编译报错

    //connect(this, SIGNAL(printLog2(int,int)), this, SLOT(onPrintLog2(int))); //编译没问题，运行没问题
    //connect(this, &Widget::printLog2, this, &Widget::onPrintLog2); //编译没问题，运行没问题

    //connect(this, SIGNAL(printLog3()), this, SLOT(onPrintLog3(int))); //编译没问题，运行报错
    //connect(this, &Widget::printLog3, this, &Widget::onPrintLog3); //编译报错

    //connect(this, SIGNAL(printLog4(char)), this, SLOT(onPrintLog4(int))); //编译没问题，运行报错
    //connect(this, &Widget::printLog4, this, &Widget::onPrintLog4); //编译、运行都没问题

    //connect(this, SIGNAL(printLog5(double)), this, SLOT(onPrintLog5(int))); //编译没问题，运行报错
    connect(this, &Widget::printLog5, this, &Widget::onPrintLog5); //编译、运行都没问题

    //因此，大部分情况下，推荐使用函数指针的方式，但下面情况会出现问题
    //因为valueChanged存在函数重载，此情况下使用函数指针，connect不知道使用哪个valueChanged，只能其进行强转
    //connect(ui->spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &Widget::onNumChanged);
    //这时候使用宏写法就更简单
    connect(ui->spinBox,  SIGNAL(valueChanged(int)), this, SLOT(onNumChanged(int)));
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
    //emit printLog(1);
    //emit printLog1(1);
    //emit printLog2(1,2);
    //emit printLog3();
    //emit printLog4('A');
    emit printLog5(36.88);
}

void Widget::onPrintLog1(QString val)
{
    qDebug() << "onPrintLog1";
}

void Widget::onPrintLog2(int a)
{
    qDebug() << "onPrintLog2" << a;
}

void Widget::onPrintLog3(int a)
{
    qDebug() << "onPrintLog3";
}

void Widget::onPrintLog4(int a)
{
    qDebug() << "onPrintLog4" << a;
}

void Widget::onPrintLog5(int a)
{
    qDebug() << "onPrintLog5" << a;
}

//void Widget::onPrintLog(int a)
//{
//    qDebug() << "onPrintLog";
//}
