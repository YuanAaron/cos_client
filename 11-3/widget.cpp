#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->lineEdit->installEventFilter(this); //让Widget捕获传递给LineEdit的事件
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "QWidget keyPressEvent";
    QWidget::keyPressEvent(event);
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit)
    {
        if(event->type()==QEvent::KeyPress)
        {
            qDebug() << "QWidget eventFilter";
        }
    }

    return QWidget::eventFilter(watched, event);
}

