﻿#include "bucketstablewidget.h"
#include "ui_bucketstablewidget.h"

#include "src/middle/managerglobal.h"
#include "src/middle/managermodel.h"
#include <QDebug>
#include <src/fend/uidelegate/bucketdelegate.h>
#include <src/middle/signals/managersignals.h>
#include "src/bend/gateway.h"
#include "src/config/api.h"
#include <QJsonObject>

BucketsTableWidget::BucketsTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BucketsTableWidget)
{
    ui->setupUi(this);

    ui->tableView->setModel(MG->m_model->modelBuckets());
//    ui->tableView->setItemDelegate(new BucketDelegate());
    ui->tableView->setItemDelegateForColumn(1,new BucketDelegate());

    //设置表格标题栏的标题（放到了ManagerModel中）

    //设置表格标题栏的宽度
    ui->tableView->setColumnWidth(0,200);
    ui->tableView->setColumnWidth(1,120);
    //ui->tableView->setColumnWidth(2,200);
    ui->tableView->horizontalHeader()->setStretchLastSection(true); //设置最后一列占满剩余的表格

    //隐藏垂直标题栏
    ui->tableView->verticalHeader()->setHidden(true);

    //设置鼠标点击排序
    ui->tableView->setSortingEnabled(true);

    //初始化翻页按钮
    ui->widgetPage->setMaxRowList(QList<int>() << 2 << 5 << 10);
    connect(ui->widgetPage, &PageWidget::pageNumChanged, this, &BucketsTableWidget::onPageNumChanged);
    connect(MG->m_signal, &ManagerSignals::bucketsSuccess, this, &BucketsTableWidget::onBucketsSuccess);
}

BucketsTableWidget::~BucketsTableWidget()
{
    delete ui;
    qDebug() << "delete BucketsTableWidget";
}

void BucketsTableWidget::on_tableView_doubleClicked(const QModelIndex &index)
{
    if(index.column() == 0)
    {
        QJsonObject params;
        params["bucketName"] = index.data().toString();
        params["dir"] = "";
        MG->m_gate->send(API::OBJECTS::LIST, params);
    }
}

void BucketsTableWidget::onPageNumChanged(int start, int maxLen)
{
    QStandardItemModel* model = MG->m_model->modelBuckets();
    for(int i=0; i<model->rowCount(); i++)
    {
        bool hidden = (i<start || i>=start+maxLen);
        ui->tableView->setRowHidden(i,hidden);
    }
}

void BucketsTableWidget::onBucketsSuccess(const QList<MyBucket> &buckets)
{
    ui->widgetPage->setTotalRow(buckets.size());
}
