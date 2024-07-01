#include "dialog.h"
#include "ui_dialog.h"

#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    //确认登录 勾选autoDefault和default，取消按钮 勾选autoDefault: 输入内容后，回车默认点击 确认登录 按钮
    //两者都只勾选autoDefault: 同上
    //前者 啥都不选，后者勾选autoDefault:  输入内容后，回车默认点击 取消登录 按钮
    //结论：autoDefault和default的优先级问题，后者更高
    qDebug()<< QString::fromLocal8Bit("确认登录");
}

void Dialog::on_pushButton_2_clicked()
{
    qDebug()<< QString::fromLocal8Bit("取消登录");
}
