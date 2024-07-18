#ifndef WAITER_H
#define WAITER_H

#include "cook.h"
#include "foods.h"

#include <QObject>
#include <QMap>

class Waiter : public QObject
{
    Q_OBJECT
public:
    explicit Waiter(QObject *parent = nullptr);
    ~Waiter();

    void initMenu();
    void order(const QString& name);

    QMap<QString, Dishes*> menu() const;

signals:

private:
    QMap<QString, Dishes*> m_menu;
    Cook m_cook;

};

#endif // WAITER_H
