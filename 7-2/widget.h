﻿#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_winPos_clicked();

    void on_winSize_clicked();

    void on_btnPosSize_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
