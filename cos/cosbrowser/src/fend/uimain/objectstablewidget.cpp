#include "objectstablewidget.h"
#include "ui_objectstablewidget.h"

#include <QDebug>
#include "src/middle/managerglobal.h"
#include "src/middle/managermodel.h"
#include "src/bend/gateway.h"
#include "src/config/api.h"

ObjectsTableWidget::ObjectsTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectsWidget)
{
    ui->setupUi(this);
    ui->tableView->setModel(MG->m_model->modelObjects());

    //设置表格标题栏的标题（放到了ManagerModel中）

    // 设置表格标题栏的宽度
    ui->tableView->setColumnWidth(0, 200);
    ui->tableView->setColumnWidth(1, 120);
    ui->tableView->horizontalHeader()->setStretchLastSection(true); //设置最后一列占满剩余的表格

    // 隐藏垂直标题
    ui->tableView->verticalHeader()->setHidden(true);

    // 设置鼠标点击排序
    ui->tableView->setSortingEnabled(true);
}

ObjectsTableWidget::~ObjectsTableWidget()
{
    delete ui;
    qDebug() << "delete ObjectsTableWidget";
}

void ObjectsTableWidget::on_btnBuckets_clicked()
{
    MG->m_gate->send(API::BUCKETS::LIST);
}
