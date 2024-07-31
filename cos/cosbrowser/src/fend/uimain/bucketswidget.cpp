#include "bucketswidget.h"
#include "ui_bucketswidget.h"

#include "src/middle/managerglobal.h"
#include "src/middle/managermodel.h"
#include <QDebug>

BucketsWidget::BucketsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BucketsWidget)
{
    ui->setupUi(this);
    ui->listView->setModel(MG->m_model->model());
}

BucketsWidget::~BucketsWidget()
{
    delete ui;
    qDebug() << "delete BucketsWidget";
}
