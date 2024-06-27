#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxValueChanged(int)));
    connect(this, SIGNAL(numChanged(int)), this, SLOT(onNumChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onSpinBoxValueChanged(int val)
{
    qDebug()<<"onSpinBoxValueChanged";
    emit numChanged(val);
}

void Widget::onNumChanged(int val)
{
    qDebug("onNumChanged");
    ui->progressBar->setValue(val);
}

