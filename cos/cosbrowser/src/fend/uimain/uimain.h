#ifndef UIMAIN_H
#define UIMAIN_H

#include <src/fend/uicommon/cosdialog.h>

namespace Ui {
class UiMain;
}

//class LoginDialog;

class UiMain : public CosDialog
{
    Q_OBJECT

public:
    explicit UiMain(QWidget *parent = nullptr);
    ~UiMain();

//    void showLoginDialog();

protected slots:
//    void onRefresh();

//    void onBtnClicked(const QString& text);
    void onUnLogin();

private:
    Ui::UiMain *ui;
//    LoginDialog* m_loginDialog = nullptr;
};

#endif // UIMAIN_H
