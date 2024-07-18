#include "waiter.h"

#include <QDebug>

Waiter::Waiter(QObject *parent) : QObject(parent)
{
    initMenu();
}

Waiter::~Waiter()
{
    qDeleteAll(m_menu.begin(),m_menu.end());
    m_menu.clear();
}

void Waiter::initMenu()
{
    QList<Dishes*> dishesList;
    dishesList << new MaPoDouFu() << new GongBaoJiDing() << new YuXiangRouSi();
    for(auto& d : qAsConst(dishesList))
    {
        m_menu[d->name()] = d;
    }
}

void Waiter::order(const QString &name)
{
    Dishes* d = m_menu.value(name);
    d = static_cast<Dishes*>(d->metaObject()->newInstance());
    connect(d, &Dishes::finished, this, [](const QString& name) {
       qDebug() << QString::fromLocal8Bit("服务员收到菜品已制作完成：") + name;
    });
    m_cook.work(d);
}

QMap<QString, Dishes *> Waiter::menu() const
{
    return m_menu;
}
