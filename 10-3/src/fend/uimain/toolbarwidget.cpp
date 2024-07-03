#include "toolbarwidget.h"
#include "ui_toolbarwidget.h"

#include <QFileDialog>
#include <QDebug>

ToolbarWidget::ToolbarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolbarWidget)
{
    ui->setupUi(this);
    connect(ui->btnQuit, &QPushButton::clicked, this, &ToolbarWidget::quitLogin);
}

ToolbarWidget::~ToolbarWidget()
{
    delete ui;
}

void ToolbarWidget::on_btnUpload_clicked()
{
    //上传单个文件
//    QString path = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("上传"), "./");
//    if(path != "")
//    {
//        qDebug() <<path.toLocal8Bit().data();
//    }
    //上传多个文件
//    QStringList pathList = QFileDialog::getOpenFileNames(this, QString::fromLocal8Bit("上传"),
//                                                         "./", "hpp(*.h *.cpp);;Makefile(*.Debug *.Release)");
//    if(pathList.size())
//    {
//        qDebug() <<pathList;
//    }
    //上传文件夹
    QString path = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("上传"),"./");
    if(path != "")
    {
        qDebug() << path.toLocal8Bit().data();
    }
}

void ToolbarWidget::on_btnDownload_clicked()
{
    // 下载文件（这里只是返回一个下载路径，而非下载的文件）
    QString path = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("下载"),
                                 "./", "hpp(*.h *.cpp);;Makefile(*.Debug *.Release)");
    if(path != "")
    {
        qDebug() <<path.toLocal8Bit().data();
    }
}
