#include "bucketstablewidget.h"
#include "ui_bucketstablewidget.h"

#include "src/middle/managerglobal.h"
#include "src/middle/managermodel.h"
#include <QDebug>
#include <src/fend/uidelegate/bucketdelegate.h>

BucketsTableWidget::BucketsTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BucketsTableWidget)
{
    ui->setupUi(this);

    ui->tableView->setModel(MG->m_model->model());
//    ui->tableView->setItemDelegate(new BucketDelegate());
    ui->tableView->setItemDelegateForColumn(1,new BucketDelegate());

    //设置表格标题栏的标题
    QStandardItemModel* model = MG->m_model->model();
    QStringList labels;
    labels << QString::fromLocal8Bit("桶名称")
           << QString::fromLocal8Bit("地区")
           << QString::fromLocal8Bit("创建时间");
    model->setColumnCount(3);
    model->setHorizontalHeaderLabels(labels);

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
