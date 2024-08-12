#ifndef UIMAIN_H
#define UIMAIN_H

#include <src/fend/uicommon/cosdialog.h>

#include <src/middle/models/cloudmodels.h>

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

    void onBucketsSuccess(const QList<MyBucket>& buckets);
    void onObjectsSuccess(const QList<MyObject>& objects);

private:
    Ui::UiMain *ui;
//    LoginDialog* m_loginDialog = nullptr;
};

#endif // UIMAIN_H
