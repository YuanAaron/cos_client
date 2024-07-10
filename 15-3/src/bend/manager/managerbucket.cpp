#include "managerbucket.h"

#include <QDebug>

Q_GLOBAL_STATIC(ManagerBucket, ins)

ManagerBucket::ManagerBucket(QObject *parent) : QObject(parent)
{

}

ManagerBucket *ManagerBucket::instance()
{
    return ins();
}

void ManagerBucket::print()
{
    qDebug() << QString::fromLocal8Bit("单例模式");
}
