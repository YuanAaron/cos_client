#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
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


void Widget::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("上传"), "./");
    if(path != "")
    {
        qDebug() << path;
        QString style = "border-image:url(\"" + path + "\");";
        qDebug() << style;
        ui->frame_2->setStyleSheet(style);
    }
}
