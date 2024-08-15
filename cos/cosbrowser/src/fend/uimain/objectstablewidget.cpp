#include "objectstablewidget.h"
#include "ui_objectstablewidget.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QUuid>
#include "src/middle/managerglobal.h"
#include "src/bend/manager/managercloud.h"
#include "src/middle/managermodel.h"
#include "src/bend/gateway.h"
#include "src/config/api.h"
#include <QJsonObject>
#include <src/fend/uidelegate/tableitemdelegate.h>
#include <src/middle/signals/managersignals.h>

ObjectsTableWidget::ObjectsTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectsWidget)
{
    ui->setupUi(this);
    //美化 创建桶 按钮
    ui->btnBuckets->setProperty("style_button", "main");
    //美化：鼠标悬停（不是选中哦），整行而非item hover的效果实现
    ui->tableView->setItemDelegate(new TableItemDelegate(ui->tableView));

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
    //关心 上传成功 的信号
    connect(MG->m_signal, &ManagerSignals::uploadSuccess, this, &ObjectsTableWidget::onUploadSuccess);
    //关心 下载成功 的信号
    connect(MG->m_signal, &ManagerSignals::downloadSuccess, this, &ObjectsTableWidget::onDownloadSuccess);
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

    //美化：设置QTableView的行高
    QStandardItemModel* model = MG->m_model->modelObjects();
    for(int i=0; i<model->rowCount(); i++)
    {
        ui->tableView->setRowHeight(i,40);
    }
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

void ObjectsTableWidget::on_btnUpload_clicked()
{
    //上传
    static QString lastDir = "./";
    //获取本地文件
    QString filePath = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("上传文件"), lastDir);
//    qDebug() << filePath;
    QFileInfo info(filePath);
    if(info.isFile() && info.exists())
    {
        QJsonObject params;
        QString jobId = QUuid::createUuid().toString();
        filePath = filePath.replace("\\", "/");
        QString key = MG->m_cloud->getCurrentDir() + info.fileName();
//        qDebug() << MG->m_cloud->getCurrentDir() << info.fileName();

        params["jobId"] = jobId;
        params["bucketName"] = MG->m_cloud->getCurrentBucketName();
        params["key"] = key;
        params["localPath"] = filePath;
        MG->m_gate->send(API::OBJECTS::PUT, params);
        lastDir = info.dir().absolutePath();
//        qDebug() << lastDir;
        emit MG->m_signal->startUpload(jobId, key, filePath);
    }

}

void ObjectsTableWidget::onUploadSuccess(const QString &jobId)
{
    on_btnRefresh_clicked();

    showMessage(QString::fromLocal8Bit("上传文件"), QString::fromLocal8Bit("文件上传成功"));
}

void ObjectsTableWidget::on_btnDownload_clicked()
{
    QModelIndex idx = ui->tableView->currentIndex();
    if(!idx.isValid())
    {
        showMessage(QString::fromLocal8Bit("下载文件"),
                    QString::fromLocal8Bit("请选择要下载的文件"));
        return;
    }

    MyObject obj = idx.data(Qt::UserRole).value<MyObject>();
    if(obj.isDir())
    {
        showMessage(QString::fromLocal8Bit("下载文件"),
                    QString::fromLocal8Bit("只能选择文件进行下载"));
        return;
    }

    //下载文件
    static QString lastDir = "./";
    QString name = idx.data().toString();

    QString filePath = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("下载文件"),
                                 FileHelper::joinPath(lastDir, name));
//    qDebug() << filePath;
    if(!filePath.isEmpty())
    {
        QFileInfo info(filePath);

        QString jobId = QUuid::createUuid().toString();
        filePath = filePath.replace("\\", "/");
        QString key = MG->m_cloud->getCurrentDir() + name;
//        qDebug() << MG->m_cloud->getCurrentDir() << name;

        QJsonObject params;
        params["jobId"] = jobId;
        params["bucketName"] = MG->m_cloud->getCurrentBucketName();
        params["key"] = key;
        params["localPath"] = filePath;
        MG->m_gate->send(API::OBJECTS::GET, params);
        lastDir = info.dir().absolutePath();
//        qDebug() << lastDir;
        emit MG->m_signal->startDownload(jobId, key, filePath, obj.size);
    }
}

void ObjectsTableWidget::onDownloadSuccess(const QString &jobId)
{
    showMessage(QString::fromLocal8Bit("下载文件"),
                QString::fromLocal8Bit("下载成功"));
}

void ObjectsTableWidget::showMessage(const QString& title, const QString& info)
{
    QMessageBox box(QMessageBox::Information,
                    title,
                    info,
                    QMessageBox::Yes);
    box.setButtonText(QMessageBox::Yes, QString::fromLocal8Bit("确定"));
    box.exec();
}
