#include "widget.h"
#include "ui_widget.h"

#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //根据菜单创建菜单按钮
    QMap<QString, Dishes*> dishesMap = m_waiter.menu();
    for(auto& d : dishesMap)
    {
        QPushButton* btn = new QPushButton(d->name());
        ui->verticalLayout->addWidget(btn);
        connect(btn, SIGNAL(clicked()), this, SLOT(onOrder()));
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onOrder()
{
    QPushButton* btn = static_cast<QPushButton*>(sender());
    m_waiter.order(btn->text());
}

