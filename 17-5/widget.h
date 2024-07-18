#ifndef WIDGET_H
#define WIDGET_H

#include "waiter.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onOrder();

private:
    Ui::Widget *ui;
    Waiter m_waiter;
};
#endif // WIDGET_H
