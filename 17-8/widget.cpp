#include "widget.h"
#include "ui_widget.h"

#include "counter.h"

#include <QFutureSynchronizer>
#include <QtConcurrent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QThreadPool::globalInstance()->setMaxThreadCount(2);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnStart_clicked()
{
    Counter::zero();
    //QFutureSynchronizer与加锁无关，主要用来监听所有QFuture，等待他们运行结束
    QFutureSynchronizer<void> sync;
    sync.addFuture(QtConcurrent::run(Counter::increment));
    sync.addFuture(QtConcurrent::run(Counter::decrement));
    sync.waitForFinished();
    qDebug() << Counter::value();
}
