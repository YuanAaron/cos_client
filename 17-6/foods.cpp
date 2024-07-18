#include "foods.h"

#include <QDebug>
#include <QThread>

Dishes::Dishes()
{

}

void Dishes::run()
{
    qDebug() << QString::fromLocal8Bit("开始制作 %1").arg(name()) << QThread::currentThreadId();
    QThread::sleep(cost());
    qDebug() << QString::fromLocal8Bit("结束制作 %1").arg(name());
    emit finishedDishes(name());
}
