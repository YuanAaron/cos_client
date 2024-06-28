#include "widget.h"
#include "ui_widget.h"

#include <QMovie>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPixmap pixmap(QString::fromLocal8Bit("C:/Users/oshacker/Documents/qt/7-5/霸气.jpg"));
    ui->label_11->setPixmap(pixmap);
    ui->label_11->setScaledContents(true);

    QMovie* movie = new QMovie(QString::fromLocal8Bit("C:/Users/oshacker/Documents/qt/7-5/鼓掌.gif"));
    ui->label_12->setMovie(movie);
    ui->label_12->setScaledContents(true);
    movie->start();
}

Widget::~Widget()
{
    delete ui;
}

