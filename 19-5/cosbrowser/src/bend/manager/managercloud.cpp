#include "managercloud.h"

#include <QDebug>

#include <src/middle/models/mybucket.h>
#include <src/bend/dao/clouds/daocloudsmock.h>
#include <src/plugins/managerplugin.h>

Q_GLOBAL_STATIC(ManagerCloud, ins)

ManagerCloud::ManagerCloud(QObject *parent) : QObject(parent)
{
    qDebug() << QString::fromLocal8Bit("只进来了一次，我是单例的!");
    m_model = new QStandardItemModel(this);
}

ManagerCloud *ManagerCloud::instance()
{
    return ins();
}

void ManagerCloud::print()
{
    qDebug() << QString::fromLocal8Bit("MB是单例的吗？");
}

void ManagerCloud::setBucket()
{
    DaoClouds* dao = MP->clouds();
    QList<MyBucket> buckets = dao->buckets();

    m_model->setRowCount(buckets.size());
//    m_model->setColumnCount(3); //objectswidget.cpp已经设置过了

    for(int i=0; i<buckets.size(); i++)
    {
        const MyBucket& bucket = buckets[i];

        QModelIndex index0 = m_model->index(i,0);
        m_model->setData(index0,bucket.name);
        m_model->setData(index0,QString::fromLocal8Bit("存储桶名称: %1").arg(bucket.name), Qt::ToolTipRole); //数据角色
        QModelIndex index1 = m_model->index(i,1);
        m_model->setData(index1,bucket.location);
        QModelIndex index2 = m_model->index(i,2);
        m_model->setData(index2,bucket.createDate);
    }

    //设置默认按照创建时间倒序
    m_model->sort(2,Qt::DescendingOrder);
}

QStandardItemModel *ManagerCloud::model() const
{
    return m_model;
}
