#include "uimain.h"
#include "ui_uimain.h"

UiMain::UiMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiMain)
{
    ui->setupUi(this);

    //使用分割器后，设置窗口占用的初始比例
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,4);
}

UiMain::~UiMain()
{
    delete ui;
}
