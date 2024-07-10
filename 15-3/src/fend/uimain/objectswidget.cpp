#include "objectswidget.h"
#include "ui_objectswidget.h"

#include "src/bend/manager/managerbucket.h"
#include <QDebug>
#include <src/fend/uidelegate/bucketdelegate.h>

ObjectsWidget::ObjectsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectsWidget)
{
    ui->setupUi(this);
    ui->tableView->setModel(MB->model());
//    ui->tableView->setItemDelegate(new BucketDelegate());
    ui->tableView->setItemDelegateForColumn(1,new BucketDelegate());
}

ObjectsWidget::~ObjectsWidget()
{
    delete ui;
    qDebug() << "delete ObjectsWidget";
}
