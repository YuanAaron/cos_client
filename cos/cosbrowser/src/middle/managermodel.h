#ifndef MANAGERMODEL_H
#define MANAGERMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <src/middle/models/mybucket.h>

class ManagerModel: public QObject
{
    Q_OBJECT
public:
    ManagerModel(QObject* parent = nullptr);

    QStandardItemModel *model() const;

private slots:
    void setBuckets(const QList<MyBucket>& buckets);

private:
    QStandardItemModel* m_model = nullptr; //这里好像不加也不会报错
};

#endif // MANAGERMODEL_H
