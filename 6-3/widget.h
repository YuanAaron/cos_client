#ifndef WIDGET_H
#define WIDGET_H

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

signals:
    void numChanged(int val);

    void printLog(int a);

private slots:
    //void onSpinBoxValueChanged(int val);
    void onNumChanged(int val);

    void on_pushButton_clicked();
    void onPrintLog(int a);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
