#ifndef MANAGERBUCKET_H
#define MANAGERBUCKET_H

#include <QObject>
#define MB ManagerBucket::instance()

class ManagerBucket : public QObject
{
    Q_OBJECT
public:
    //不要直接构造函数创建对象，直接使用instance来使用对象即可
    explicit ManagerBucket(QObject *parent = nullptr);

    static ManagerBucket* instance();

    void print();

signals:

};

#endif // MANAGERBUCKET_H
