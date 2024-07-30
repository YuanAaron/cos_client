#include "managersignals.h"

ManagerSignals::ManagerSignals(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QList<MyBucket>>("QList<MyBucket>");
}

ManagerSignals::~ManagerSignals()
{
    qDebug("delete ManagerSignals");
}
