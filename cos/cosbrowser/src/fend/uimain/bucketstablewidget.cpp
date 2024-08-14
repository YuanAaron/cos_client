#include "bucketstablewidget.h"
#include "createbucketdialog.h"
#include "ui_bucketstablewidget.h"

#include "src/middle/managerglobal.h"
#include "src/middle/managermodel.h"
#include <QDebug>
#include <src/fend/uidelegate/bucketdelegate.h>
#include <src/middle/signals/managersignals.h>
#include "src/bend/gateway.h"
#include "src/config/api.h"
#include <QAction>
#include <QJsonObject>
#include <QMessageBox>

BucketsTableWidget::BucketsTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BucketsTableWidget)
{
    ui->setupUi(this);

    ui->tableView->setModel(MG->m_model->modelBuckets());
//    ui->tableView->setItemDelegate(new BucketDelegate());
    ui->tableView->setItemDelegateForColumn(1,new BucketDelegate());

    //设置表格标题栏的标题（放到了ManagerModel中）

    //设置表格标题栏的宽度
    ui->tableView->setColumnWidth(0,200);
    ui->tableView->setColumnWidth(1,120);
    //ui->tableView->setColumnWidth(2,200);
    ui->tableView->horizontalHeader()->setStretchLastSection(true); //设置最后一列占满剩余的表格

    //隐藏垂直标题栏
    ui->tableView->verticalHeader()->setHidden(true);

    //设置鼠标点击排序
    ui->tableView->setSortingEnabled(true);

    //初始化翻页按钮
    ui->widgetPage->setMaxRowList(QList<int>() << 2 << 5 << 10);
    connect(ui->widgetPage, &PageWidget::pageNumChanged, this, &BucketsTableWidget::onPageNumChanged);
    connect(MG->m_signal, &ManagerSignals::bucketsSuccess, this, &BucketsTableWidget::onBucketsSuccess);

    //删除桶
    //1.创建右键菜单
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction* delAction = new QAction(QString::fromLocal8Bit("删除"),this);
    connect(delAction, &QAction::triggered, this, &BucketsTableWidget::onDeleteBucket);
    ui->tableView->addAction(delAction);
}

BucketsTableWidget::~BucketsTableWidget()
{
    delete ui;
    qDebug() << "delete BucketsTableWidget";
}

void BucketsTableWidget::on_tableView_doubleClicked(const QModelIndex &index)
{
    if(index.column() == 0)
    {
        QJsonObject params;
        params["bucketName"] = index.data().toString();
        params["dir"] = "";
        MG->m_gate->send(API::OBJECTS::LIST, params);
    }
}

void BucketsTableWidget::onPageNumChanged(int start, int maxLen)
{
    QStandardItemModel* model = MG->m_model->modelBuckets();
    for(int i=0; i<model->rowCount(); i++)
    {
        bool hidden = (i<start || i>=start+maxLen);
        ui->tableView->setRowHidden(i,hidden);
    }
}

void BucketsTableWidget::onBucketsSuccess(const QList<MyBucket> &buckets)
{
    ui->widgetPage->setTotalRow(buckets.size());
}

void BucketsTableWidget::on_btnCreateBucket_clicked()
{
//    CreateBucketDialog dialog(this); //这样写会报错，CreateBucketDialog的创建跟前面的LoginDialog、UiMain不应该是一样的吗？
    CreateBucketDialog dialog;
    int ret = dialog.exec();
    if(ret == QDialog::Accepted)
    {
        MyBucket bucket = dialog.getBucket();
        if(bucket.isValid())
        {
            QJsonObject params;
            params["bucketName"] = bucket.name;
            params["location"] = bucket.location;
            MG->m_gate->send(API::BUCKETS::PUT, params);
        }
    }
}

void BucketsTableWidget::onDeleteBucket()
{
    //删除桶
    //2.弹出提示信息
    QModelIndex idx = ui->tableView->currentIndex();
    if(idx.isValid())
    {
        QString name = idx.data().toString();

        //按钮为英文的写法
//        int ret = QMessageBox::question(this, QString::fromLocal8Bit("删除桶"),
//                              QString::fromLocal8Bit("是否确认删除桶【%1】吗？").arg(name));

        //按钮为中文的写法
        QMessageBox box(QMessageBox::Question, QString::fromLocal8Bit("删除桶"),
                        QString::fromLocal8Bit("是否确认删除桶【%1】吗？").arg(name),
                        QMessageBox::Yes|QMessageBox::No);
        box.setButtonText(QMessageBox::Yes, QString::fromLocal8Bit("删除"));
        box.setButtonText(QMessageBox::No, QString::fromLocal8Bit("取消"));
        int ret = box.exec();

        if(ret == QMessageBox::Yes)
        {
            QJsonObject params;
            params["bucketName"] = name;
            MG->m_gate->send(API::BUCKETS::DEL, params);
        }
    }
}

void BucketsTableWidget::on_btnRefresh_clicked()
{
    MG->m_gate->send(API::BUCKETS::LIST);
}
