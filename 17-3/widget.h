#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mythread.h"

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
    void on_btnStartSearch_clicked();
    void onFinished();

    void on_btnStopSearch_clicked();

private:
    Ui::Widget *ui;
    MyThread* mth = nullptr;
};
#endif // WIDGET_H
