#include "transfer.h"
#include "ui_transfer.h"

#include <QDebug>

Transfer::Transfer(QWidget *parent) :
    CosDialog(parent),
    ui(new Ui::Transfer)
{
    qDebug() << QString::fromLocal8Bit("Transfer 构造");
    ui->setupUi(body());

    setTitle(QString::fromLocal8Bit("传输列表"));
    setFixedSize(600, 450);
    qDebug() << QString::fromLocal8Bit("Transfer 构造结束");
}

Transfer::~Transfer()
{
    delete ui;
    qDebug() << "delete Transfer";
}
