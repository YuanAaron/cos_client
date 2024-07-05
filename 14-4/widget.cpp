#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //让进度条以对话框的形式显示
    ui->progressBar->setWindowFlag(Qt::Dialog);
    ui->progressBar->show(); //TODO 为啥需要这步？

    connect(ui->spinBox, SIGNAL(valueChanged(int)), ui->progressBar, SLOT(setValue(int)));
    connect(ui->spinBox, SIGNAL(valueChanged(QString)), ui->progressBar, SLOT(setWindowTitle(QString)));
    connect(ui->spinBox, SIGNAL(valueChanged(QString)), ui->label, SLOT(setText(QString)));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    //断开所有连接
//    disconnect(ui->spinBox, nullptr, nullptr, nullptr); //写法一
//    ui->spinBox->disconnect(nullptr, nullptr, nullptr); //写法二

    //断开valueChanged(QString)信号的所有连接
//    disconnect(ui->spinBox, SIGNAL(valueChanged(QString)), nullptr, nullptr);

    //断开接收者ui->progressBar的所有连接
//    disconnect(ui->spinBox, nullptr, ui->progressBar, nullptr);

    //断开接收者ui->progressBar某个槽函数的连接
    disconnect(ui->spinBox, nullptr, ui->progressBar, SLOT(setWindowTitle(QString)));
}
