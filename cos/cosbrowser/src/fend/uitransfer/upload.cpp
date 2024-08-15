#include "upload.h"
#include "ui_upload.h"

#include "src/middle/managerglobal.h"
#include "src/middle/signals/managersignals.h"
#include "src/config/api.h"
#include <QDebug>
#include <src/fend/uidelegate/tableitemdelegate.h>

Upload::Upload(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Upload)
{
    qDebug() << QString::fromLocal8Bit("Upload 构造");
    ui->setupUi(this);
    initHeader();
    connect(MG->m_signal, &ManagerSignals::startUpload, this, &Upload::onStartUpload);
    connect(MG->m_signal, &ManagerSignals::uploadProcess, this, &Upload::onUploadProcess);
    connect(MG->m_signal, &ManagerSignals::uploadSuccess, this, &Upload::onUploadSuccess);
    connect(MG->m_signal, &ManagerSignals::error, this, &Upload::onError);

    //美化：鼠标悬停（不是选中哦），整行而非item hover的效果实现
    ui->tableWidget->setItemDelegate(new TableItemDelegate(ui->tableWidget));
    qDebug() << QString::fromLocal8Bit("Upload 构造结束");
}

Upload::~Upload()
{
    delete ui;
    qDebug() << "delete Upload";
}

void Upload::onStartUpload(const QString &jobId, const QString &key, const QString &localPath)
{
    //在第一行插入一行数据
    ui->tableWidget->insertRow(0);
    //美化：设置QTableWidget的行高
    ui->tableWidget->setRowHeight(0, 40);

    //更新每列的数据
    QTableWidgetItem* item = new QTableWidgetItem(key);
    item->setData(Qt::UserRole, jobId); //自定义角色
    ui->tableWidget->setItem(0, 0, item); //云端路径
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(localPath)); //本地路径
    QFileInfo info(localPath);
    ProgressWidget *bar = new ProgressWidget();
    bar->setRange(0, info.size());
    ui->tableWidget->setCellWidget(0, 2, bar); //上传状态
}

void Upload::onUploadProcess(const QString &jobId, qulonglong transferedSize, qulonglong totalSize)
{
    ProgressWidget* w = findTableWidgetItem(jobId);
    w->setValue(transferedSize);
}

void Upload::onUploadSuccess(const QString &jobId)
{
    ProgressWidget* w = findTableWidgetItem(jobId);
    w->setFinished(QString::fromLocal8Bit("上传成功"));
}

void Upload::onError(int api, const QString &msg, const QJsonValue &req)
{
    if (api != API::OBJECTS::PUT)
        return;
    ProgressWidget* w = findTableWidgetItem(req["jobId"].toString());
    w->setError(QString::fromLocal8Bit("上传失败"));
    w->setToolTip(msg);
}

ProgressWidget* Upload::findTableWidgetItem(const QString &jobId)
{
    for (int i  = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QTableWidgetItem* item = ui->tableWidget->item(i, 0);
        QString itemId = item->data(Qt::UserRole).toString();
        if (itemId == jobId)
        {
            return dynamic_cast<ProgressWidget*>(ui->tableWidget->cellWidget(i, 2));
        }
    }
    return nullptr;
}

void Upload::initHeader()
{
    QStringList headers;
    headers << QString::fromLocal8Bit("云端路径")
            << QString::fromLocal8Bit("本地路径")
            << QString::fromLocal8Bit("上传状态");
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(1);
}
