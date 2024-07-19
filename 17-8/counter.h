#ifndef COUNTER_H
#define COUNTER_H

#include <QMutex>

class Counter
{
public:
    static void increment()
    {
        for(int i=0;i<10000;i++)
        {
            mutex.lock();
            n++;
            mutex.unlock();
        }
    }

    static void decrement()
    {
        for(int i=0;i<10000;i++)
        {
            mutex.lock();
            n--;
            mutex.unlock();
        }
    }

    static int value()
    {
        return n;
    }

    static void zero()
    {
        n = 0;
    }

private:
    static int n;
    static QMutex mutex;
};

int Counter::n = 0;
QMutex Counter::mutex;

#endif // COUNTER_H
