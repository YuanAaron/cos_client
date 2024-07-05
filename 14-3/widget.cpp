#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->btnDownload, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->btnUpload, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onButtonClicked()
{
    //获取信号发出者及文本
    QPushButton* btn = dynamic_cast<QPushButton*>(sender());
    qDebug() << btn->text();
}

