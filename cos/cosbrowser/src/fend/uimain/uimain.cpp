#include "uimain.h"
#include "ui_uimain.h"

//#include <src/fend/uilogin/logindialog.h>
#include "src/middle/signals/managersignals.h"
#include "src/middle/managerglobal.h"
#include "src/config/api.h"
#include <QPushButton>

#include <QDebug>

#include <src/fend/uicommon/messagebox.h>

UiMain::UiMain(QWidget *parent) :
    CosDialog(parent),
    ui(new Ui::UiMain)
{
    qDebug() << QString::fromLocal8Bit("UiMain 构造");
    ui->setupUi(body());

    //添加传输列表和退出登录按钮
    QPushButton* transferBtn = addButton(GLOBAL::PATH::TRANS, GLOBAL::PATH::TRANS_HOVER);
    connect(transferBtn, &QPushButton::clicked, this, &UiMain::showTransfer);
    QPushButton* quitBtn = addButton(GLOBAL::PATH::QUIT, GLOBAL::PATH::QUIT_HOVER);
    //这里要进行信号传递，不能直接通过onUnLogin进行处理，因为可能有其他窗口（比如登录窗口）关心该信号
    connect(quitBtn, &QPushButton::clicked, MG->m_signal, &ManagerSignals::unLogin);

    //添加标题分割线
    addTitleLine();

    //QPushButton的大小在BaseDialog中就设置了，新添加按钮后没有再设置大小，在这里重新调用一次不合适，具体做法见本次commit
    addMinButton(GLOBAL::PATH::MIN_PATH, GLOBAL::PATH::MIN_HOVER_PATH);
    addMaxButton(GLOBAL::PATH::MAX_PATH, GLOBAL::PATH::MAX_HOVER_PATH,
                 GLOBAL::PATH::NORMAL_PATH, GLOBAL::PATH::NORMAL_HOVER_PATH);

    setTitle(QString::fromLocal8Bit("Cos Client"));
    resize(1080,640);

//    setKeyDisabled();

    //使用分割器后，设置窗口占用的初始比例
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,4);

//    connect(ui->widgetToolbar, &ToolbarWidget::refreshSig, this, &UiMain::onRefresh);

//    connect(ui->widgetToolbar, &ToolbarWidget::btnClicked, this, &UiMain::onBtnClicked);

    //关心 登录成功 的信号
    connect(MG->m_signal, &ManagerSignals::loginSuccess, this, &UiMain::show);
    //关心 退出登录 的信号
    connect(MG->m_signal, &ManagerSignals::unLogin, this, &UiMain::onUnLogin);

    //关心 获取桶列表成功 的信号
    connect(MG->m_signal, &ManagerSignals::bucketsSuccess, this, &UiMain::onBucketsSuccess);
    //关心 获取对象列表成功 的信号
    connect(MG->m_signal, &ManagerSignals::objectsSuccess, this, &UiMain::onObjectsSuccess);

    connect(MG->m_signal, &ManagerSignals::error, this, &UiMain::onError);

    if(!m_transfer)
    {
//        m_transfer = new Transfer(this); //写法报错
        m_transfer = new Transfer;
    }

    qDebug() << QString::fromLocal8Bit("UiMain 构造结束");
}

UiMain::~UiMain()
{
    delete ui;
    qDebug() << "delete UiMain";

    //未加入UiMain对象树，因此需要单独删除，否则会造成内存泄漏
//    if(m_loginDialog)
//    {
//        delete m_loginDialog;
//    }

    //自己添加
    if(m_transfer)
    {
        delete m_transfer;
        m_transfer = nullptr;
    }
}

//void UiMain::showLoginDialog()
//{
//    if(!m_loginDialog)
//    {
//        //new时没有指定其父窗口，那么它就是一个顶层窗口
//        m_loginDialog = new LoginDialog;
//        //创建登录窗口后：更新记忆的登录名（在登录窗口输入登录名后，会自动回显其他登录信息）
//        m_loginDialog->updateLoginInfo();

//        connect(m_loginDialog, &LoginDialog::accepted, this, &UiMain::show);
////        connect(ui->widgetToolbar, &ToolbarWidget::quitLogin, this, &UiMain::showLoginDialog);
//    }
//    hide();
//    m_loginDialog->show();
//}

//void UiMain::onBtnClicked(const QString &text)
//{
//    if(text == QString::fromLocal8Bit("创建桶"))
//    {
//        //处理 创建桶
//        qDebug() << "UiMain::onBtnClicked:" << text;
//    }
//    else if(text == QString::fromLocal8Bit("刷新"))
//    {
//        //处理 刷新
//        qDebug() << "UiMain::onBtnClicked:" << text;
//    }
//    else if(text == QString::fromLocal8Bit("传输列表"))
//    {
//        //处理 传输列表
//        qDebug() << "UiMain::onBtnClicked:" << text;
//    }
//    else if(text == QString::fromLocal8Bit("退出登录"))
//    {
//        onUnLogin();
//    }

//}

void UiMain::onUnLogin()
{
//    showLoginDialog();
    hide();
}

void UiMain::onBucketsSuccess(const QList<MyBucket> &buckets)
{
    ui->stackedWidget->setCurrentIndex(0);
}

void UiMain::onObjectsSuccess(const QList<MyObject> &objects)
{
    ui->stackedWidget->setCurrentIndex(1);
}

void UiMain::onError(int api, const QString &msg, const QJsonValue &req)
{
    if(api > API::BUCKETS::BASE)
    {
        MessageBox box;
        box.showMessage(QString::fromLocal8Bit("错误"), msg);
    }
}

void UiMain::showTransfer()
{
//    //他这段代码放在这里，上传/下载前点击了传输列表按钮没问题，但如果上传/下载过程中点击传输列表按钮，程序过一会就会崩溃。
      //原因：添加打印日志后发现，没有执行OnStartDownload的代码（传输按钮下载开始后才点击，错过了监听startDownload信号），
      //执行onDownloadProgress代码的过程中崩溃。
//    //解决方案：我将这段代码放到了UiMain的构造函数中，程序就不再崩溃，
//    if(!m_transfer)
//    {
////        m_transfer = new Transfer(this); //写法报错
//        m_transfer = new Transfer;
//    }
    m_transfer->show();
}

//void UiMain::onRefresh()
//{
//    qDebug() << "UiMain::onRefresh";
//}
