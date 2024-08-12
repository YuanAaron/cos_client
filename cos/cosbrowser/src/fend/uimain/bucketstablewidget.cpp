#include "bucketstablewidget.h"
#include "ui_bucketstablewidget.h"

#include "src/middle/managerglobal.h"
#include "src/middle/managermodel.h"
#include <QDebug>
#include <src/fend/uidelegate/bucketdelegate.h>
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
