#ifndef CREATEBUCKETDIALOG_H
#define CREATEBUCKETDIALOG_H

#include <QWidget>

#include <src/fend/uicommon/cosdialog.h>

#include <src/middle/models/cloudmodels.h>

namespace Ui {
class CreateBucketDialog;
}

class CreateBucketDialog : public CosDialog
{
    Q_OBJECT

public:
    explicit CreateBucketDialog(QWidget *parent = nullptr);
    ~CreateBucketDialog();

    MyBucket getBucket();

private:
    Ui::CreateBucketDialog *ui;
};

#endif // CREATEBUCKETDIALOG_H
