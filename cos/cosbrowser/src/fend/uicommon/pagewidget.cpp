#include "pagewidget.h"
#include "ui_pagewidget.h"

#include <QDebug>

PageWidget::PageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageWidget)
{
    ui->setupUi(this);
}

PageWidget::~PageWidget()
{
    delete ui;
    qDebug() << "delete PageWidget";
}
