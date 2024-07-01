﻿#include "widget.h"
#include "ui_widget.h"

#include <QCompleter>
#include <QDebug>
#include <QRegExpValidator>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置光标最初在最左边
    ui->lineEdit_3->setCursorPosition(0);

    //正则验证器
    QRegExp reg("\\d+");
    QRegExpValidator* validator = new QRegExpValidator(reg);
    ui->lineEdit_4->setValidator(validator);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text().trimmed();
    qDebug()<< text;
    qDebug()<< ui->lineEdit_2->text();
    if(historyList.contains(text))
    {
        return;
    }
    historyList << text; //historyList.append(text);
    //记忆
    QCompleter* completer = new QCompleter(historyList);
    ui->lineEdit->setCompleter(completer);
}

void Widget::on_pushButton_2_clicked()
{
    qDebug()<< QString::fromLocal8Bit("启动/禁用");
}

void Widget::on_pushButton_3_clicked()
{
    //ui->pushButton_2->setVisible(!ui->pushButton_2->isVisible());
    //ui->pushButton_2->setHidden(ui->pushButton_2->isVisible());
    if(ui->pushButton_2->isVisible())
    {
        ui->pushButton_2->hide();
    }
    else
    {
       ui->pushButton_2->show();
    }

}

void Widget::on_pushButton_4_clicked()
{
    qDebug()<<QString::fromLocal8Bit("确认登录");
}
