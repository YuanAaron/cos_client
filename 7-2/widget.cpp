#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置窗口无标题栏
    this->setWindowFlags(Qt::CustomizeWindowHint);
    //设置窗口无边框
    this->setWindowFlags(Qt::FramelessWindowHint);
    //设置窗口置顶
    //setWindowFlags(Qt::WindowStaysOnTopHint); //默认会使用上面两个设置无效
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_winPos_clicked()
{
    //设置窗口位置
    move(ui->spinBoxX->value(), ui->spinBoxY->value());
}

void Widget::on_winSize_clicked()
{
    //设置窗口大小
    //resize(ui->spinBoxWidth->value(), ui->spinBoxHeight->value());
    //设置窗口固定大小
//    setFixedWidth(ui->spinBoxWidth->value());
//    setFixedHeight(ui->spinBoxHeight->value());
    setFixedSize(ui->spinBoxWidth->value(), ui->spinBoxHeight->value());
}

void Widget::on_btnPosSize_clicked()
{
//    ui->btnPosSize->move(ui->spinBoxX->value(), ui->spinBoxY->value());
//    ui->btnPosSize->setFixedSize(ui->spinBoxWidth->value(), ui->spinBoxHeight->value());
    ui->btnPosSize->setGeometry(ui->spinBoxX->value(),
                                ui->spinBoxY->value(),
                                ui->spinBoxWidth->value(),
                                ui->spinBoxHeight->value());
}
