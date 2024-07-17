#include "usermanager.h"

#include <QDebug>

UserManager::UserManager(QObject *parent) : QObject(parent)
{
    td = new QThread();
    moveToThread(td); //当UserManager执行槽函数时，使用线程来执行
    td->start();
    qDebug() << QString::fromLocal8Bit("子线程的id") << td->currentThreadId();
}

UserManager::~UserManager()
{
    if(td->isRunning())
    {
        td->terminate();
        td->wait(1000);
    }
    delete td;
    td = nullptr;
}

void UserManager::onSearchBasic()
{
    for(int i=0;i<3;i++)
    {
        qDebug() << QString::fromLocal8Bit("查询基本信息") << i << QThread::currentThreadId();
        QThread::sleep(1);
    }
    emit searchBasicFinished(QString::fromLocal8Bit("张三"));
}

void UserManager::onSearchJob()
{
    for(int i=0;i<3;i++)
    {
        qDebug() << QString::fromLocal8Bit("查询工作信息") << i << QThread::currentThreadId();
        QThread::sleep(1);
    }
    emit searchJobFinished(QString::fromLocal8Bit("Qt工程师"));
}
