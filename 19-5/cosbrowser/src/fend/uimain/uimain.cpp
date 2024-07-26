#include "uimain.h"
#include "ui_uimain.h"

//#include <src/fend/uilogin/logindialog.h>
#include "src/middle/signals/managersignals.h"
#include "src/middle/managerglobal.h"

#include <QDebug>

UiMain::UiMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiMain)
{
    ui->setupUi(this);

    //使用分割器后，设置窗口占用的初始比例
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,4);

//    connect(ui->widgetToolbar, &ToolbarWidget::refreshSig, this, &UiMain::onRefresh);

//    connect(ui->widgetToolbar, &ToolbarWidget::btnClicked, this, &UiMain::onBtnClicked);

    //关心 登录成功 的信号
    connect(MG->m_signal, &ManagerSignals::loginSuccess, this, &UiMain::show);

    //关心 退出登录 的信号
    connect(MG->m_signal, &ManagerSignals::unLogin, this, &UiMain::onUnLogin);
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

//void UiMain::onRefresh()
//{
//    qDebug() << "UiMain::onRefresh";
//}
