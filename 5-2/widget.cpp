#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    int index = 5;
    for (int i = 0; i < 10; ++i) {
        qDebug() << "第" << i+1 << "行";
        index = i;
    }
}

