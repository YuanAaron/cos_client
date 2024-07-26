#ifndef MANAGERBUCKET_H
#define MANAGERBUCKET_H

#include <QObject>
#include <QStandardItemModel>

class ManagerCloud : public QObject
{
    Q_OBJECT
public:
    //不要直接构造函数创建对象，直接使用instance来使用对象即可
    explicit ManagerCloud(QObject *parent = nullptr);
    ~ManagerCloud();

    void print();
    void setBucket();

    QStandardItemModel *model() const;

    void login(QString secretId, QString secretKey);
signals:

private:
    QStandardItemModel* m_model = nullptr; //这里好像不加也不会报错
};

#endif // MANAGERBUCKET_H
