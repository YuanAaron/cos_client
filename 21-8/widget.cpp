#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    //实现页面循环播放
    int count = ui->stackedWidget->count();
    int idx = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex((idx+1)%count);
}
