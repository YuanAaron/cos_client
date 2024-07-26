#include "toolbarwidget.h"
#include "ui_toolbarwidget.h"
#include "src/middle/signals/managersignals.h"
#include "src/middle/managerglobal.h"

#include <QFileDialog>
#include <QDebug>
#include <QSignalMapper>

ToolbarWidget::ToolbarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolbarWidget)
{
    ui->setupUi(this);
//    connect(ui->btnQuit, &QPushButton::clicked, this, &ToolbarWidget::quitLogin);

//    connect(ui->btnRefresh, &QPushButton::clicked, this, &ToolbarWidget::refreshSig);

    //使用QSignalMapper匹配信号发送
//    QSignalMapper* mapper = new QSignalMapper(this);
//    QList<QPushButton*> buttonList = findChildren<QPushButton*>();
//    for(auto btn: buttonList)
//    {
//        //1、点击按钮触发map()槽函数，该槽函数会检查点击的按钮和文本是否是绑定关系。
//        connect(btn,SIGNAL(clicked()), mapper, SLOT(map()));
//        mapper->setMapping(btn, btn->text()); //提前将按钮和文本做好绑定、映射，作为点击时判定按钮和文本是否为绑定关系的依据
//    }

//    //2、如果是，mapper发出（统一）的mapped(QString)信号，并将该信号传递出去（传递一个btnClick(QString)的信号）
//    //3、在主窗口UiMain中通过connect获取传递出来的btnClicked(QString)信号，并通过主窗口中的onBtnClicked(QString)槽函数统一处理各个按钮的行为

//    //注意：
//    //1、当新增新的工具按钮时，只需要在主窗口的onBtnClicked(QString)中新增对应按钮的处理/槽函数即可，不再新增/修改其他代码
//    //2、不仅有mapped(QString)，还有mapped(int)/mapped(QWidget*)/mapped(QObject*)，所以如果使用mapped(int)，上边在提前绑定时可以将 按钮和一个数字 绑定，好处是在主窗口的onBtnClicked中可以使用switch
//    connect(mapper, SIGNAL(mapped(QString)), this, SIGNAL(btnClicked(QString)));
}

ToolbarWidget::~ToolbarWidget()
{
    delete ui;
    qDebug() <<"delete ToolbarWidget";
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

void ToolbarWidget::on_btnQuit_clicked()
{
    emit MG->m_signal->unLogin();
}
