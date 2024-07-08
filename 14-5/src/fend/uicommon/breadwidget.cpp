#include "breadwidget.h"
#include "ui_breadwidget.h"

#include <QDebug>

BreadWidget::BreadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BreadWidget)
{
    ui->setupUi(this);
}

BreadWidget::~BreadWidget()
{
    delete ui;
    qDebug() << "delete BreadWidget";
}
