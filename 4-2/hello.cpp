#include "hello.h"
#include "ui_hello.h"

#include <QMessageBox>

Hello::Hello(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Hello)
{
    //hello.ui文件最终会被编译系统解析，生成Ui_Hello类来描述ui界面
    //为什么传入this（细心的话会发现每个组件的构造函数都有一个parent参数）?
    //为什么Ui_Hello没有通过析构函数释放资源？
    //为什么只需要在main方法中w.show()就可以显示所有组件？
    //因为父对象显示的时候，默认会把所有的子对象显示；父对象删除的时候，会把所有子对象删除
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &Hello::showDialog); //TODO 传参不懂！！！
    setStyleSheet("QWidget{font-size:24pt;}");

//    QIcon icon;
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

