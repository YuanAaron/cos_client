#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    //设置窗口无标题栏
    this->setWindowFlags(Qt::CustomizeWindowHint);

    QPixmap pixmap("C:/Users/oshacker/Documents/qt/8-3/qt.png");
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
    close();
}
