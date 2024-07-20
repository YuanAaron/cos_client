#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginDialog; }
QT_END_NAMESPACE

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    //需求：更新记忆的登录名（在登录窗口输入登录名后，会自动回显其他登录信息）
    void updateLoginInfo();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_btnClose_clicked();

    void on_btnLogin_clicked();

private:
    Ui::LoginDialog *ui;
    QPoint m_start;
};
#endif // LOGINDIALOG_H
