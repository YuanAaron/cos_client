#include "bucketswidget.h"
#include "ui_bucketswidget.h"

#include "src/middle/managerglobal.h"
#include "src/bend/manager/managercloud.h"
#include <QDebug>

BucketsWidget::BucketsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BucketsWidget)
{
    ui->setupUi(this);
    ui->listView->setModel(MG->m_cloud->model());
}

BucketsWidget::~BucketsWidget()
{
    delete ui;
    qDebug() << "delete BucketsWidget";
}
