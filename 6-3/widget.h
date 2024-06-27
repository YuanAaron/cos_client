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

    void printLog1(int a);
    void printLog2(int a, int b);
    void printLog3();

    void printLog4(char c);
    void printLog5(double f);


private slots:
    //void onSpinBoxValueChanged(int val);
    void onNumChanged(int val);

    void on_pushButton_clicked();
    //void onPrintLog(int a);

    void onPrintLog1(QString val);
    void onPrintLog2(int a);
    void onPrintLog3(int a);

    void onPrintLog4(int a);
    void onPrintLog5(int a);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
