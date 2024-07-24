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

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    //设置窗口无标题栏
    this->setWindowFlags(Qt::CustomizeWindowHint);

//    QPixmap pixmap("C:/Users/oshacker/Documents/qt/10-3/qt.png");
////    ui->labelLogo->setPixmap(pixmap);
////    ui->labelLogo->setScaledContents(true);
//    ui->labelLogo->setPixmap(pixmap.scaled(ui->labelLogo->size()));

    ui->lineSecretKey->installEventFilter(this);

    //设置"登录窗口"的样式
    ui->labelTitle->setProperty("style","h3");
    ui->labelLgoinName->setProperty("style","h4");
    ui->labelSecretId->setProperty("style","h4");
    ui->labelSecretKey->setProperty("style","h4");
    ui->labelRemark->setProperty("style","h4");
    ui->btnClose->setProperty("style","h3");
    ui->btnLogin->setProperty("style","h4");
}

LoginDialog::~LoginDialog()
{
    delete ui;
    qDebug() << "delete LoginDialog";
}

void LoginDialog::mousePressEvent(QMouseEvent *e)
{
    //鼠标左键
    if(e->button() == Qt::LeftButton)
    {
        m_start = e->pos(); //相对于父控件坐标原点的位置
    }
    QDialog::mousePressEvent(e);

}

void LoginDialog::mouseMoveEvent(QMouseEvent *e)
{
//    qDebug() << e->buttons()<<Qt::LeftButton;
    //原项目中使用e->buttons() & Qt::LeftButton屏蔽右键，这样即可同时按下鼠标左右键（右键被屏蔽了）也可以移动窗口
    if(e->buttons() == Qt::LeftButton)
    {
        QPoint target =  e->pos() - m_start + pos();
        this->move(target);
    }
    QDialog::mouseMoveEvent(e);
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
    QStringList historyList = MDB->loginNameList();
    QCompleter* completer = new QCompleter(historyList);
    ui->lineLoginName->setCompleter(completer);

    connect(completer, static_cast<void (QCompleter::*)(const QString &)>(&QCompleter::activated),
            [&](const QString& name){
            LoginInfo info = MDB->loginInfoByName(name);
            ui->lineSecretId->setText(info.secretId);
            ui->lineSecretKey->setText(info.secretKey);
            ui->lineRemark->setText(info.remark);
            ui->checkSaveSession->setChecked(true);
    });

    connect(ui->lineLoginName, &QLineEdit::editingFinished,
            [this](){
            LoginInfo info = MDB->loginInfoByName(ui->lineLoginName->text().trimmed());
            if(info.name=="")
            {
                ui->lineSecretId->setText(info.secretId);
                ui->lineSecretKey->setText(info.secretKey);
                ui->lineRemark->setText(info.remark);
                ui->checkSaveSession->setChecked(false);
            }
    });
}


void LoginDialog::on_btnClose_clicked()
{
    //如果最后一个可见主窗口（即没有父窗口），发出QApplication::lastWindowClosed信号，则qt退出事件循环，从而终止程序。
    //close();

    //Hides the modal dialog and sets the result code to Rejected.
    //搞不懂为什么换成了这个？
    reject();
}

//测试网关
void LoginDialog::on_btnLogin_clicked()
{
    QJsonObject params;
    params["secretId"] = ui->lineSecretId->text().trimmed();
    params["secretKey"] = ui->lineSecretKey->text().trimmed();
    GW->send(API::LOGIN::NORMAL, params);
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
