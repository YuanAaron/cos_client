#include "bucketswidget.h"
#include "ui_bucketswidget.h"

#include "src/bend/manager/managerbucket.h"
#include <QDebug>

BucketsWidget::BucketsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BucketsWidget)
{
    ui->setupUi(this);
    ui->listView->setModel(MB->model());
}

BucketsWidget::~BucketsWidget()
{
    delete ui;
    qDebug() << "delete BucketsWidget";
}
