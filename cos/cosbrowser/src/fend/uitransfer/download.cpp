#include "download.h"
#include "ui_download.h"

#include "src/middle/managerglobal.h"
#include "src/middle/signals/managersignals.h"
#include "src/config/api.h"
#include <QDebug>

Download::Download(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Download)
{
    ui->setupUi(this);

    qDebug() << QString::fromLocal8Bit("Download构造");
    initHeader();
    connect(MG->m_signal, &ManagerSignals::startDownload, this, &Download::onStartDownload);
    connect(MG->m_signal, &ManagerSignals::downloadProcess, this, &Download::onDownloadProcess);
    connect(MG->m_signal, &ManagerSignals::downloadSuccess, this, &Download::onDownloadSuccess);
    connect(MG->m_signal, &ManagerSignals::error, this, &Download::onError);
    qDebug() << QString::fromLocal8Bit("Download构造结束");
}

Download::~Download()
{
    delete ui;
    qDebug() << "delete Download";
}

void Download::onStartDownload(const QString& jobId, const QString& key, const QString& localPath, qulonglong total)
{
    ui->tableWidget->insertRow(0);
    ui->tableWidget->setRowHeight(0, 40);
    QTableWidgetItem* item = new QTableWidgetItem(key);
    item->setData(Qt::UserRole, jobId);
    ui->tableWidget->setItem(0, 0, item);
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(localPath));

    ProgressWidget *bar = new ProgressWidget();
    bar->setRange(0, total);
    ui->tableWidget->setCellWidget(0, 2, bar);
}

void Download::onDownloadProcess(const QString &jobId, qulonglong transferedSize, qulonglong totalSize)
{
    ProgressWidget* w = findTableWidgetItem(jobId);
    w->setValue(transferedSize);
}

void Download::onDownloadSuccess(const QString &jobId)
{
    ProgressWidget* w = findTableWidgetItem(jobId);
    w->setFinished(QString::fromLocal8Bit("下载成功"));
}

void Download::onError(int api, const QString &msg, const QJsonValue &req)
{
    if (api != API::OBJECTS::GET)
        return;
    ProgressWidget* w = findTableWidgetItem(req["jobId"].toString());
    w->setError(QString::fromLocal8Bit("下载失败"));
    w->setToolTip(msg);
}

ProgressWidget* Download::findTableWidgetItem(const QString &jobId)
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

void Download::initHeader()
{
    QStringList headers;
    headers << QString::fromLocal8Bit("云端路径")
            << QString::fromLocal8Bit("本地路径")
            << QString::fromLocal8Bit("下载状态");
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(1);
}
