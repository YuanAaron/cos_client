#include "mythread.h"
#include <QDebug>

MyThread::MyThread(QObject* parent):QThread(parent)
{

}

void MyThread::stop()
{
    is_stop = true;
    bool ok = wait(6000);
    if(ok)
    {
        qDebug() << QString::fromLocal8Bit("等待线程结束成功");
    }
    else
    {
        qDebug() << QString::fromLocal8Bit("等待线程结束失败");
        terminate(); //强制关闭线程
        wait(1000); //让主线程等待子线程关闭结束
    }
}

//模拟数据库查询
void MyThread::run()
{
    is_stop = false;
    qDebug() << QString::fromLocal8Bit("当前线程id：") << this->thread()->currentThreadId();
    for(int i=0;i<100;i++)
    {
        qDebug() << QString::fromLocal8Bit("正在查询数据库") << i;
        if(is_stop)
        {
            qDebug() << QString::fromLocal8Bit("终止查询");
//            sleep(5); //wait函数返回true
            sleep(30); //wait函数返回false
            return;
        }
        sleep(1);
    }
    qDebug() << QString::fromLocal8Bit("数据库查询结束");
}
