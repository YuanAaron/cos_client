#ifndef FOODS_H
#define FOODS_H

#include <QFutureWatcher>
#include <QObject>
#include <QRunnable>

class Dishes : public QFutureWatcher<void>
{
    Q_OBJECT
public:
    Dishes();

    // 获取菜名
    virtual QString name() = 0;
    // 获取做菜耗时
    virtual int cost() = 0;

signals:
    void finishedDishes(const QString& name);

public:
    void run();
};

class MaPoDouFu: public Dishes
{
    Q_OBJECT
public:
    Q_INVOKABLE MaPoDouFu(){};
    QString name() {return QString::fromLocal8Bit("麻婆豆腐");}
    int cost(){return 3;}
};

class GongBaoJiDing: public Dishes
{
    Q_OBJECT
public:
    Q_INVOKABLE GongBaoJiDing(){};
    QString name() {return QString::fromLocal8Bit("宫保鸡丁");}
    int cost(){return 5;}
};

class YuXiangRouSi: public Dishes
{
    Q_OBJECT
public:
    Q_INVOKABLE YuXiangRouSi(){};
    QString name() {return QString::fromLocal8Bit("鱼香肉丝");}
    int cost(){return 5;}
};

#endif // FOODS_H
