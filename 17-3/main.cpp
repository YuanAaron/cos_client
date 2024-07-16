#include "widget.h"

#include <QApplication>
#include <QDebug>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    qDebug() << QString::fromLocal8Bit("当前线程id：") << a.thread()->currentThreadId();

    w.show();
    return a.exec();
}
