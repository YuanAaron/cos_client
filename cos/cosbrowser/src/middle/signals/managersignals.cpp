#include "managersignals.h"

ManagerSignals::ManagerSignals(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QList<MyBucket>>("QList<MyBucket>");
    qRegisterMetaType<QList<MyObject>>("QList<MyObject>");
}

ManagerSignals::~ManagerSignals()
{
    qDebug("delete ManagerSignals");
}
