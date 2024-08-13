#include "createbucketdialog.h"
#include "ui_createbucketdialog.h"

#include "src/config/global.h"
#include <QDebug>

CreateBucketDialog::CreateBucketDialog(QWidget *parent) :
    CosDialog(parent),
    ui(new Ui::CreateBucketDialog)
{
    ui->setupUi(body());
    resize(400,150);

    ui->comboBoxLocation->addItems(GLOBAL::LOCATION_LIST);

    connect(ui->btnOK, &QPushButton::clicked, this, &CreateBucketDialog::accept);
    connect(ui->btnCancel, &QPushButton::clicked, this, &CreateBucketDialog::reject);
}

CreateBucketDialog::~CreateBucketDialog()
{
    delete ui;
    qDebug() << "delete CreateBucketDialog";
}

MyBucket CreateBucketDialog::getBucket()
{
    MyBucket bucket;
    bucket.name = ui->lineName->text().trimmed();
    bucket.location = ui->comboBoxLocation->currentText();
    return bucket;
}
