#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxValueChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onSpinBoxValueChanged(int val)
{
    ui->progressBar->setValue(val);
}

void Widget::onNumChanged(int val)
{
    ui->progressBar->setValue(val);
}

