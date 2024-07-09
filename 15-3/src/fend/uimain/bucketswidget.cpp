#include "bucketswidget.h"
#include "ui_bucketswidget.h"

#include <QDebug>

BucketsWidget::BucketsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BucketsWidget)
{
    ui->setupUi(this);
}

BucketsWidget::~BucketsWidget()
{
    delete ui;
    qDebug() << "delete BucketsWidget";
}
