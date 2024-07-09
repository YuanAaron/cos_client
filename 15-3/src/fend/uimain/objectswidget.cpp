#include "objectswidget.h"
#include "ui_objectswidget.h"

#include <QDebug>

ObjectsWidget::ObjectsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectsWidget)
{
    ui->setupUi(this);
}

ObjectsWidget::~ObjectsWidget()
{
    delete ui;
    qDebug() << "delete ObjectsWidget";
}
