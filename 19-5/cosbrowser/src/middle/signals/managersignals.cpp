#include "managersignals.h"

ManagerSignals::ManagerSignals(QObject *parent) : QObject(parent)
{

}

ManagerSignals::~ManagerSignals()
{
    qDebug("delete ManagerSignals");
}
