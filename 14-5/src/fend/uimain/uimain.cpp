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
    if(m_loginDialog)
    {
        delete m_loginDialog;
    }
}

void UiMain::showLoginDialog()
{
    if(!m_loginDialog)
    {
        m_loginDialog = new LoginDialog;

        connect(m_loginDialog, &LoginDialog::accepted, this, &UiMain::show);
        connect(ui->widgetToolbar, &ToolbarWidget::quitLogin, this, &UiMain::showLoginDialog);
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

}

//void UiMain::onRefresh()
//{
//    qDebug() << "UiMain::onRefresh";
//}
