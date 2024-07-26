#include "managersignals.h"

Q_GLOBAL_STATIC(ManagerSignals,ins)

ManagerSignals::ManagerSignals(QObject *parent) : QObject(parent)
{

}

ManagerSignals *ManagerSignals::instance()
{
    return ins();
}
