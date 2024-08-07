#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <src/fend/uicommon/cosdialog.h>


QT_BEGIN_NAMESPACE
namespace Ui { class LoginDialog; }
QT_END_NAMESPACE

class LoginDialog : public CosDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    //需求：更新记忆的登录名（在登录窗口输入登录名后，会自动回显其他登录信息）
    void updateLoginInfo();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void onBtnLoginClicked();

    void onLoginSucceed();
    void onLoginError(int api, const QString& msg);

private:
    Ui::LoginDialog *ui;
};
#endif // LOGINDIALOG_H
