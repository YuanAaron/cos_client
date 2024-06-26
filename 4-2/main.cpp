#include "hello.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //每个Qt窗口应用程序都需要一个QApplication对象
    Hello w;
    w.show();
    return a.exec(); //让程序进入事件循环，作用：接收来自用户的事件，如鼠标事件、键盘事件。
}
