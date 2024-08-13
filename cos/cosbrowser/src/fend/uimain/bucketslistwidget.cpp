#include "bucketslistwidget.h"
#include "ui_bucketslistwidget.h"

#include "src/middle/managerglobal.h"
#include "src/middle/managermodel.h"
#include "src/bend/gateway.h"
#include "src/config/api.h"
#include <QDebug>
#include <QJsonObject>
#include <src/fend/uicommon/comboline.h>
#include <src/middle/signals/managersignals.h>

BucketsListWidget::BucketsListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BucketsWidget)
{
    ui->setupUi(this);
    ui->listView->setModel(MG->m_model->modelBuckets());

    //搜索桶
    //1.搜索框触发查询桶内容操作
    connect(ui->lineEdit, &ComboLine::itemSelected, this, &BucketsListWidget::showBucketObjects);
    connect(MG->m_signal, &ManagerSignals::bucketsSuccess, this, &BucketsListWidget::onBucketsSuccess);

    //2.搜索框和桶列表实现筛选功能
    connect(ui->lineEdit, &ComboLine::textEdited, this, &BucketsListWidget::onTextEdited);
}

BucketsListWidget::~BucketsListWidget()
{
    delete ui;
    qDebug() << "delete BucketsWidget";
}

void BucketsListWidget::on_listView_doubleClicked(const QModelIndex &index)
{
    showBucketObjects(index.data().toString());
}

void BucketsListWidget::showBucketObjects(const QString &bucketName)
{
    QJsonObject params;
    params["bucketName"] = bucketName;
    params["dir"] = "";
    MG->m_gate->send(API::OBJECTS::LIST, params);
}

void BucketsListWidget::onBucketsSuccess(const QList<MyBucket> &buckets)
{
    QStringList words;
    for(const auto& bucket: qAsConst(buckets))
    {
        words.append(bucket.name);
    }
    ui->lineEdit->setWords(words);
}

void BucketsListWidget::onTextEdited(const QString &text)
{
    QStandardItemModel* model = MG->m_model->modelBuckets();
    for(int i=0; i<model->rowCount(); i++)
    {
        bool hidden = !(model->index(i,0).data().toString().contains(text));
//        bool hidden = !(model->item(i)->text().contains(text));
        ui->listView->setRowHidden(i,hidden);
    }
}
