#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
public:
    MyThread(QObject* parent = nullptr);

    void stop();

protected:
    void run() override;

private:
    bool is_stop = true;
};

#endif // MYTHREAD_H
