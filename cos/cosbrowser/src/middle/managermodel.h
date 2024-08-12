#ifndef MANAGERMODEL_H
#define MANAGERMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <src/middle/models/cloudmodels.h>

class ManagerModel: public QObject
{
    Q_OBJECT
public:
    ManagerModel(QObject* parent = nullptr);

    QStandardItemModel *modelBuckets() const;
    QStandardItemModel *modelObjects() const;

private slots:
    void setBuckets(const QList<MyBucket>& buckets);
    void setObjects(const QList<MyObject>& objects);

private:
    void initBucketsTable();
    void initObjectsTable();

private:
    QStandardItemModel* m_modelBuckets = nullptr; //这里好像不加也不会报错 //存储桶表格模型
    QStandardItemModel* m_modelObjects = nullptr; //对象表格模型
};

#endif // MANAGERMODEL_H
