#include "cook.h"

#include <QThreadPool>
#include <QtConcurrent>
#include <QFuture>

Cook::Cook()
{
    //设置有2名厨师
    QThreadPool::globalInstance()->setMaxThreadCount(2);
}

void Cook::work(Dishes* dishes)
{
    //选择一名厨师进行烹饪，如果没有厨师空闲，则进入排队
//    QThreadPool::globalInstance()->start(dishes);
    QFuture<void> f = QtConcurrent::run(dishes, &Dishes::run);
    dishes->setFuture(f); //让watcher监视线程的执行情况
}
