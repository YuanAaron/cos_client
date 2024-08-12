#include "bucketslistwidget.h"
#include "ui_bucketslistwidget.h"

#include "src/middle/managerglobal.h"
#include "src/middle/managermodel.h"
#include "src/bend/gateway.h"
#include "src/config/api.h"
#include <QDebug>
#include <QJsonObject>

BucketsListWidget::BucketsListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BucketsWidget)
{
    ui->setupUi(this);
    ui->listView->setModel(MG->m_model->modelBuckets());
}

BucketsListWidget::~BucketsListWidget()
{
    delete ui;
    qDebug() << "delete BucketsWidget";
}

void BucketsListWidget::on_listView_doubleClicked(const QModelIndex &index)
{
    QJsonObject params;
    params["bucketName"] = index.data().toString();
    params["dir"] = "";
    MG->m_gate->send(API::OBJECTS::LIST, params);
}
