#include "cosdialog.h"
#include "ui_cosdialog.h"
#include "src/config/global.h"
#include "ui_basedialog.h"

#include <QDebug>

CosDialog::CosDialog(QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::CosDialog)
{
    ui->setupUi(body()); //将父组件改为basedialog.ui中的widgetBody

    setLogo(GLOBAL::PATH::LOGO_PATH);
    setTitle(QString::fromLocal8Bit("Cos"));
    m_ui->labelLogo->setFixedSize(32, 24);

    m_ui->labelTitle->setProperty("style", "h4"); //从logindialog中提取为通用的
}

CosDialog::~CosDialog()
{
    delete ui;
    qDebug() << "delete CosDialog";
}
