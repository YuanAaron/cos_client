#include "bucketslistwidget.h"
#include "ui_bucketslistwidget.h"

#include "src/middle/managerglobal.h"
#include "src/middle/managermodel.h"
#include <QDebug>

BucketsListWidget::BucketsListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BucketsWidget)
{
    ui->setupUi(this);
    ui->listView->setModel(MG->m_model->model());
}

BucketsListWidget::~BucketsListWidget()
{
    delete ui;
    qDebug() << "delete BucketsWidget";
}
