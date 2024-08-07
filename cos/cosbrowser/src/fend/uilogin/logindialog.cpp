#include "logindialog.h"
#include "ui_logindialog.h"

#include <QMessageBox>
#include <QMouseEvent>
#include <QDebug>
#include <QCompleter>
#include <QJsonObject>
#include <src/bend/manager/managerdb.h>
#include "src/bend/gateway.h"
#include "src/config/api.h"
#include "src/middle/signals/managersignals.h"
#include "src/middle/managerglobal.h"

LoginDialog::LoginDialog(QWidget *parent)
    : CosDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(body());

    setTitle(QString::fromLocal8Bit("登录"));

    ui->lineSecretKey->installEventFilter(this);

    //设置"登录窗口"的样式
    ui->labelLgoinName->setProperty("style","h5");
    ui->labelSecretId->setProperty("style","h5");
    ui->labelSecretKey->setProperty("style","h5");
    ui->labelRemark->setProperty("style","h5");
    ui->btnLogin->setProperty("style","h5");

    //手动修改logindialog的xml，导致 登录按钮 的自动绑定失效
    connect(ui->btnLogin, &QPushButton::clicked, this, &LoginDialog::onBtnLoginClicked);

    //关心 登录成功 的信号
    connect(MG->m_signal,&ManagerSignals::loginSuccess, this, &LoginDialog::onLoginSucceed);
    //关系 错误(这里指登录失败） 的信号
    connect(MG->m_signal,&ManagerSignals::error, this, &LoginDialog::onLoginError);

    //关心 退出登录 的信号
    connect(MG->m_signal,&ManagerSignals::unLogin, this, &LoginDialog::show);
    updateLoginInfo();
}

LoginDialog::~LoginDialog()
{
    delete ui;
    qDebug() << "delete LoginDialog";
}

bool LoginDialog::eventFilter(QObject *watched, QEvent *event)
{
    //watched：需要关注的控件对象
    //event：传递给事件对象的事件
    if(watched == ui->lineSecretKey)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent* e = static_cast<QKeyEvent*>(event);
            //捕获Ctrl+C和Ctrl+V
            if(e->modifiers() == Qt::ControlModifier)
            {
                if(e->key() == Qt::Key_C || e->key() == Qt::Key_V)
                {
                    return true; //true表示事件已被处理，不再向下传递；false表示继续传递
                }
            }
        }
    }
    return QDialog::eventFilter(watched, event);
}

void LoginDialog::updateLoginInfo()
{
    QStringList historyList = MG->m_db->loginNameList();
    QCompleter* completer = new QCompleter(historyList);
    ui->lineLoginName->setCompleter(completer);

    connect(completer, static_cast<void (QCompleter::*)(const QString &)>(&QCompleter::activated),
            [&](const QString& name){
            LoginInfo info = MG->m_db->loginInfoByName(name);
            ui->lineSecretId->setText(info.secretId);
            ui->lineSecretKey->setText(info.secretKey);
            ui->lineRemark->setText(info.remark);
            ui->checkSaveSession->setChecked(true);
    });

    connect(ui->lineLoginName, &QLineEdit::editingFinished,
            [this](){
            LoginInfo info = MG->m_db->loginInfoByName(ui->lineLoginName->text().trimmed());
            if(info.name=="")
            {
                ui->lineSecretId->setText(info.secretId);
                ui->lineSecretKey->setText(info.secretKey);
                ui->lineRemark->setText(info.remark);
                ui->checkSaveSession->setChecked(false);
            }
    });
}

//测试网关
void LoginDialog::onBtnLoginClicked()
{
    QJsonObject params;
    params["secretId"] = ui->lineSecretId->text().trimmed();
    params["secretKey"] = ui->lineSecretKey->text().trimmed();
    MG->m_gate->send(API::LOGIN::NORMAL, params);
}

void LoginDialog::onLoginSucceed()
{
    //Hides the modal dialog and sets the result code to Accepted.
    accept();
    //是否选择了记住会话
    if(ui->checkSaveSession->isChecked())
    {
        //保存登录信息
        MG->m_db->saveLoginInfo(ui->lineLoginName->text(),
                           ui->lineSecretId->text(),
                           ui->lineSecretKey->text(),
                           ui->lineRemark->text());

        //登录成功后：更新记忆的登录名（在登录窗口输入登录名后，会自动回显其他登录信息）
        updateLoginInfo();
    }
    else
    {
        //删除登录信息
        MG->m_db->removeLoginInfo(ui->lineSecretId->text());
    }
}

void LoginDialog::onLoginError(int api, const QString &msg)
{
    if(api != API::LOGIN::NORMAL)
        return;

    QMessageBox::warning(this,QString::fromLocal8Bit("登录失败"),
                                 QString::fromLocal8Bit("登录失败：%1").arg(msg));
}

//void LoginDialog::on_btnLogin_clicked()
//{
//    //登录信息验证
//    if(ui->lineSecretId->text().trimmed()=="zhangsan"
//            && ui->lineSecretKey->text().trimmed()=="123")
//    {
//        //Hides the modal dialog and sets the result code to Accepted.
//        accept();
//        //是否选择了记住会话
//        if(ui->checkSaveSession->isChecked())
//        {
//            //保存登录信息
//            MDB->saveLoginInfo(ui->lineLoginName->text(),
//                               ui->lineSecretId->text(),
//                               ui->lineSecretKey->text(),
//                               ui->lineRemark->text());
//        }
//        else
//        {
//            //删除登录信息
//            MDB->removeLoginInfo(ui->lineSecretId->text());
//        }

//        //登录成功后：更新记忆的登录名（在登录窗口输入登录名后，会自动回显其他登录信息）
//        updateLoginInfo();
//    }
//    else
//    {
//        QMessageBox::warning(this,QString::fromLocal8Bit("登录失败"),
//                             QString::fromLocal8Bit("请检查SecretId或SecretKey是否正确"));
//    }
//}

//void LoginDialog::on_btnLogin_clicked()
//{
//    //登录信息验证
//    if(ui->lineSecretId->text().trimmed()=="zhangsan"
//            && ui->lineSecretKey->text().trimmed()=="123")
//    {
//        //Hides the modal dialog and sets the result code to Accepted.
//        accept();
//        //是否选择了记住会话
//        if(ui->checkSaveSession->isChecked())
//        {
//            //保存登录信息
//            MDB->saveLoginInfo(ui->lineLoginName->text(),
//                               ui->lineSecretId->text(),
//                               ui->lineSecretKey->text(),
//                               ui->lineRemark->text());
//        }
//        else
//        {
//            //删除登录信息
//            MDB->removeLoginInfo(ui->lineSecretId->text());
//        }

//        //登录成功后：更新记忆的登录名（在登录窗口输入登录名后，会自动回显其他登录信息）
//        updateLoginInfo();
//    }
//    else
//    {
//        QMessageBox::warning(this,QString::fromLocal8Bit("登录失败"),
//                             QString::fromLocal8Bit("请检查SecretId或SecretKey是否正确"));
//    }
//}
