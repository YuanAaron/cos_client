#include "managermodel.h"

#include <src/bend/dao/clouds/daocloudsmock.h>
#include <src/plugins/managerplugin.h>
#include "src/middle/managerglobal.h"
#include "src/middle/signals/managersignals.h"

ManagerModel::ManagerModel(QObject* parent)
        :QObject(parent)
{
    m_model = new QStandardItemModel(this);
    //关心 bucketsSuccess信号
    connect(MG->m_signal, &ManagerSignals::bucketsSuccess, this, &ManagerModel::setBuckets);
}

void ManagerModel::setBuckets(const QList<MyBucket>& buckets)
{
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

QStandardItemModel *ManagerModel::model() const
{
    return m_model;
}
