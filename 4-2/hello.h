#ifndef HELLO_H
#define HELLO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Hello; }
QT_END_NAMESPACE

class Hello : public QWidget //QWidget是所有应用程序窗口类的基类
{
    Q_OBJECT //支持Qt的特性，如信号槽、对象树、元对象等

public:
    Hello(QWidget *parent = nullptr); //parent == nullptr时，该窗口为独立窗口，可在任务栏看到；否则，该窗口为主窗口的控件。
    ~Hello();

private slots:
    void showDialog();

private:
    Ui::Hello *ui;
};
#endif // HELLO_H
