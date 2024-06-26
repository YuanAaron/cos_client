#include "hello.h"
#include "ui_hello.h"

#include <QMessageBox>

Hello::Hello(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Hello)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &Hello::showDialog); //TODO 传参不懂！！！
    setStyleSheet("QWidget{font-size:24pt;}");

//    QIcon ico                   n;
//    icon.addFile("C:/Users/oshacker/Documents/qt/4-2/images/logo.ico");
//    //设置窗口图标（当设置了应用程序图标后，不需要再额外设置窗口图标）
//    setWindowIcon(icon);
}

Hello::~Hello()
{
    delete ui;
}

void Hello::showDialog()
{
    QMessageBox::information(this,QString::fromLocal8Bit("你好"),QString::fromLocal8Bit("你好，我是对象存储浏览器"));
}

