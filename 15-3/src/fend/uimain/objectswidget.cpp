#include "objectswidget.h"
#include "ui_objectswidget.h"

#include "src/bend/manager/managerbucket.h"
#include <QDebug>

ObjectsWidget::ObjectsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectsWidget)
{
    ui->setupUi(this);
    ui->tableView->setModel(MB->model());
}

ObjectsWidget::~ObjectsWidget()
{
    delete ui;
    qDebug() << "delete ObjectsWidget";
}
