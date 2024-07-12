#include "uimain.h"
#include "ui_uimain.h"

#include <src/fend/uilogin/logindialog.h>

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

    connect(ui->widgetToolbar, &ToolbarWidget::btnClicked, this, &UiMain::onBtnClicked);
}

UiMain::~UiMain()
{
    delete ui;
    qDebug() << "delete UiMain";

    //未加入UiMain对象树，因此需要单独删除，否则会造成内存泄漏
    if(m_loginDialog)
    {
        delete m_loginDialog;
    }
}

void UiMain::showLoginDialog()
{
    if(!m_loginDialog)
    {
        //new时没有指定其父窗口，那么它就是一个顶层窗口
        m_loginDialog = new LoginDialog;

        connect(m_loginDialog, &LoginDialog::accepted, this, &UiMain::show);
//        connect(ui->widgetToolbar, &ToolbarWidget::quitLogin, this, &UiMain::showLoginDialog);
    }
    hide();
    m_loginDialog->show();
}

void UiMain::onBtnClicked(const QString &text)
{
    if(text == QString::fromLocal8Bit("创建桶"))
    {
        //处理 创建桶
        qDebug() << "UiMain::onBtnClicked:" << text;
    }
    else if(text == QString::fromLocal8Bit("刷新"))
    {
        //处理 刷新
        qDebug() << "UiMain::onBtnClicked:" << text;
    }
    else if(text == QString::fromLocal8Bit("传输列表"))
    {
        //处理 传输列表
        qDebug() << "UiMain::onBtnClicked:" << text;
    }
    else if(text == QString::fromLocal8Bit("退出登录"))
    {
        onUnLogin();
    }

}

void UiMain::onUnLogin()
{
    showLoginDialog();
}

//void UiMain::onRefresh()
//{
//    qDebug() << "UiMain::onRefresh";
//}
