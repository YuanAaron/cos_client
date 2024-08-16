#include "managermodel.h"

#include <src/bend/dao/clouds/daocloudsmock.h>
#include <src/plugins/managerplugin.h>
#include "src/middle/managerglobal.h"
#include "src/middle/signals/managersignals.h"
#include "src/config/global.h"

ManagerModel::ManagerModel(QObject* parent)
        :QObject(parent)
{
    m_modelBuckets = new QStandardItemModel(this);
    m_modelObjects = new QStandardItemModel(this);
    initBucketsTable();
    initObjectsTable();
    //关心 bucketsSuccess信号
    connect(MG->m_signal, &ManagerSignals::bucketsSuccess, this, &ManagerModel::setBuckets);
    //关心 objectsSuccess信号
    connect(MG->m_signal, &ManagerSignals::objectsSuccess, this, &ManagerModel::setObjects);
}

void ManagerModel::setBuckets(const QList<MyBucket>& buckets)
{
    m_modelBuckets->setRowCount(buckets.size());
//    m_model->setColumnCount(3); //objectswidget.cpp已经设置过了

    for(int i=0; i<buckets.size(); i++)
    {
        const MyBucket& bucket = buckets[i];

        QModelIndex index0 = m_modelBuckets->index(i,0);
        m_modelBuckets->setData(index0,bucket.name);
        m_modelBuckets->setData(index0,QString::fromLocal8Bit("存储桶名称: %1").arg(bucket.name), Qt::ToolTipRole); //数据角色
        //在桶前添加图标
        m_modelBuckets->setData(index0,QIcon(GLOBAL::PATH::BUCKET),Qt::DecorationRole);

        QModelIndex index1 = m_modelBuckets->index(i,1);
        m_modelBuckets->setData(index1,bucket.location);
        QModelIndex index2 = m_modelBuckets->index(i,2);
        m_modelBuckets->setData(index2,bucket.createDate);
    }

    //设置默认按照创建时间倒序
    m_modelBuckets->sort(2,Qt::DescendingOrder);
}

void ManagerModel::setObjects(const QList<MyObject> &objects)
{
    m_modelObjects->setRowCount(objects.size());
//    m_model->setColumnCount(3); //objectswidget.cpp已经设置过了

    for(int i=0; i<objects.size(); i++)
    {
        const MyObject& obj = objects[i];

        QModelIndex index0 = m_modelObjects->index(i,0);
        m_modelObjects->setData(index0,obj.name);
        QVariant var;
        var.setValue(obj);
        m_modelObjects->setData(index0,var,Qt::UserRole);
        //在对象前添加图标
        if(obj.isDir())
        {
            m_modelObjects->setData(index0,QIcon(GLOBAL::PATH::DIR),Qt::DecorationRole);
        }
        else
        {
            m_modelObjects->setData(index0,QIcon(GLOBAL::PATH::FILE),Qt::DecorationRole);
        }

        QModelIndex index1 = m_modelObjects->index(i,1);
        m_modelObjects->setData(index1,obj.size);

        QModelIndex index2 = m_modelObjects->index(i,2);
        m_modelObjects->setData(index2,obj.lastmodified);
    }
}

void ManagerModel::initBucketsTable()
{
    //设置桶表格标题栏的标题
    QStringList labels;
    labels << QString::fromLocal8Bit("桶名称")
           << QString::fromLocal8Bit("地区")
           << QString::fromLocal8Bit("创建时间");
    m_modelBuckets->setColumnCount(labels.size()); //写死的3修改为labels.size()
    m_modelBuckets->setHorizontalHeaderLabels(labels);
}

void ManagerModel::initObjectsTable()
{
    //设置对象表格标题栏的标题
    QStringList labels;
    labels << QString::fromLocal8Bit("对象名称")
           << QString::fromLocal8Bit("大小")
           << QString::fromLocal8Bit("更新时间");
    m_modelObjects->setColumnCount(labels.size()); //写死的3修改为labels.size()
    m_modelObjects->setHorizontalHeaderLabels(labels);
}

QStandardItemModel *ManagerModel::modelObjects() const
{
    return m_modelObjects;
}

QStandardItemModel *ManagerModel::modelBuckets() const
{
    return m_modelBuckets;
}
