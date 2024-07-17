#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    manager = new UserManager();
    connect(this, &Widget::searchBasic, manager, &UserManager::onSearchBasic);
    connect(this, &Widget::searchJob, manager, &UserManager::onSearchJob);

    connect(manager, &UserManager::searchBasicFinished, this, &Widget::onSearchBasicFinished);
    connect(manager, &UserManager::searchJobFinished, this, &Widget::onSearchJobFinished);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnSearchBasic_clicked()
{
    //查询用户基本信息
    emit searchBasic();
    ui->textEditBasic->append(QString::fromLocal8Bit("查询基本信息，已发送"));
}

void Widget::on_btnSearchJob_clicked()
{
    //查询工作信息
    emit searchJob();
    ui->textEditJob->append(QString::fromLocal8Bit("查询工作信息，已发送"));
}

void Widget::onSearchBasicFinished(const QString &name)
{
    ui->textEditBasic->append(QString::fromLocal8Bit("查询基本信息，已接收：") + name);
}

void Widget::onSearchJobFinished(const QString &name)
{
    ui->textEditJob->append(QString::fromLocal8Bit("查询工作信息，已接收：") + name);
}
