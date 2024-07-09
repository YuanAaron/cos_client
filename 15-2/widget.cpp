#include "widget.h"
#include "ui_widget.h"

#include <QFileSystemModel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,4);
    ui->splitter->setStretchFactor(2,2);

    QFileSystemModel* model = new QFileSystemModel(this);
    model->setRootPath(QDir::currentPath());

    ui->listView->setModel(model);
    ui->listView->setRootIndex(model->index(QDir::currentPath()));

    ui->tableView->setModel(model);
    ui->tableView->setRootIndex(model->index(QDir::currentPath()));

    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(QDir::currentPath()));
}

Widget::~Widget()
{
    delete ui;
}

