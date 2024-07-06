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

//void UiMain::onRefresh()
//{
//    qDebug() << "UiMain::onRefresh";
//}
