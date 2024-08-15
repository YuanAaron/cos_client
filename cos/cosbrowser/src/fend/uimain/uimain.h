#ifndef UIMAIN_H
#define UIMAIN_H

#include <src/fend/uicommon/cosdialog.h>

#include <src/middle/models/cloudmodels.h>

#include <src/fend/uitransfer/transfer.h>

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

    void onError(int api, const QString& msg, const QJsonValue& req);
    void showTransfer();

private:
    Ui::UiMain *ui;
//    LoginDialog* m_loginDialog = nullptr;
    Transfer* m_transfer = nullptr;
};

#endif // UIMAIN_H
