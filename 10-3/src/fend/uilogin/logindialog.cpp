#include "logindialog.h"
#include "ui_logindialog.h"

#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    //设置窗口无标题栏
    this->setWindowFlags(Qt::CustomizeWindowHint);

    QPixmap pixmap("C:/Users/oshacker/Documents/qt/10-3/qt.png");
//    ui->labelLogo->setPixmap(pixmap);
//    ui->labelLogo->setScaledContents(true);
    ui->labelLogo->setPixmap(pixmap.scaled(ui->labelLogo->size()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}


void LoginDialog::on_btnClose_clicked()
{
    //如果最后一个可见主窗口（即没有父窗口），发出QApplication::lastWindowClosed信号，则qt退出事件循环，从而终止程序。
    //close();

    //Hides the modal dialog and sets the result code to Rejected.
    //搞不懂为什么换成了这个？
    reject();
}

void LoginDialog::on_btnLogin_clicked()
{
    //登录信息验证
    if(ui->lineSecretId->text().trimmed()=="zhangsan"
            && ui->lineSecretKey->text().trimmed()=="123")
    {
        //Hides the modal dialog and sets the result code to Accepted.
        accept();
    }
    else
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("登录失败"),
                             QString::fromLocal8Bit("请检查SecretId或SecretKey是否正确"));
    }
}
