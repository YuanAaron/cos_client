#include "objectstablewidget.h"
#include "ui_objectstablewidget.h"

#include <QDebug>
#include "src/middle/managerglobal.h"
#include "src/bend/manager/managercloud.h"
#include "src/middle/managermodel.h"
#include "src/bend/gateway.h"
#include "src/config/api.h"
#include <QJsonObject>
#include <src/middle/signals/managersignals.h>

ObjectsTableWidget::ObjectsTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectsWidget)
{
    ui->setupUi(this);
    ui->tableView->setModel(MG->m_model->modelObjects());

    //设置表格标题栏的标题（放到了ManagerModel中）

    // 设置表格标题栏的宽度
    ui->tableView->setColumnWidth(0, 200);
    ui->tableView->setColumnWidth(1, 120);
    ui->tableView->horizontalHeader()->setStretchLastSection(true); //设置最后一列占满剩余的表格

    // 隐藏垂直标题
    ui->tableView->verticalHeader()->setHidden(true);

    // 设置鼠标点击排序
    ui->tableView->setSortingEnabled(true);

    // 初始化翻页按钮
    ui->widgetPage->setMaxRowList(QList<int>() << 5 << 10 << 20);
    connect(ui->widgetPage, &PageWidget::pageNumChanged, this, &ObjectsTableWidget::onPageNumChanged);

    //关心 获取对象列表成功 的信号
    connect(MG->m_signal, &ManagerSignals::objectsSuccess, this, &ObjectsTableWidget::onObjectsSuccess);
    //关心 面包屑的pathChanged 信号
    connect(ui->widgetBread, &BreadWidget::pathChanged, this, &ObjectsTableWidget::onPathChanged);
}

ObjectsTableWidget::~ObjectsTableWidget()
{
    delete ui;
    qDebug() << "delete ObjectsTableWidget";
}

void ObjectsTableWidget::on_btnBuckets_clicked()
{
    MG->m_gate->send(API::BUCKETS::LIST);
}

void ObjectsTableWidget::on_tableView_doubleClicked(const QModelIndex &index)
{
    //MyCustomStruct c1 = v.value<MyCustomStruct>();
    MyObject obj = index.data(Qt::UserRole).value<MyObject>();
    if(obj.isDir())
    {
        QJsonObject params;
        params["bucketName"] = MG->m_cloud->getCurrentBucketName();
        params["dir"] = obj.key;
        MG->m_gate->send(API::OBJECTS::LIST, params);
    }
}

void ObjectsTableWidget::onObjectsSuccess(const QList<MyObject> &objects)
{
    QString path = MG->m_cloud->getCurrentBucketName() + "/" + MG->m_cloud->getCurrentDir();
    ui->widgetBread->setPath(path);
    ui->widgetPage->setTotalRow(objects.size());
}

void ObjectsTableWidget::onPathChanged(const QString &newPath)
{
    // newPath=file-1300416378/test/bll
    // 需要将newPath 转化为 test/bll/
    QString key = newPath+"/";
    key = key.mid(key.indexOf("/")+1);

    QJsonObject params;
    params["bucketName"] = MG->m_cloud->getCurrentBucketName();
    params["dir"] = key;
    MG->m_gate->send(API::OBJECTS::LIST, params);
}

void ObjectsTableWidget::onPageNumChanged(int start, int maxLen)
{
    QStandardItemModel* model = MG->m_model->modelObjects();
    for(int i=0; i<model->rowCount(); i++)
    {
        bool hidden = (i<start || i>=start+maxLen);
        ui->tableView->setRowHidden(i,hidden);
    }
}

void ObjectsTableWidget::on_btnRefresh_clicked()
{
    onPathChanged(ui->widgetBread->currentPath());
}
