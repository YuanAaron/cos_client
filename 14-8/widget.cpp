#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMetaObject>
#include <QPushButton>
#include <QMetaMethod>
#include "mylabel.h"
#include "mylineedit.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::doCommon(const QMetaObject& obj)
{
    qDebug() << obj.className();
    qDebug() << obj.inherits(&QWidget::staticMetaObject); //在Qt中，每个继承自QObject的类都有一个static QMetaObject staticMetaObject，它包含了关于该类的元对象信息。
    qDebug() << obj.property(0).typeName() << obj.property(0).name();
}

void Widget::doCommon2(const QMetaObject& obj, const QString& text)
{
    QObject* object = obj.newInstance();
    qDebug() << object;

    //将object添加到布局管理器中
    QWidget* w = dynamic_cast<QWidget*>(object);
    ui->verticalLayout->insertWidget(1, w);

    //调用w对象的setText方法
    obj.invokeMethod(w, "setText", Q_ARG(QString, text));
}


void Widget::on_pushButton_clicked()
{
    // 获取基本信息
//    doCommon(*ui->pushButton->metaObject());

    if (ui->comboBox->currentIndex() == 0)  // MyLabel
    {
        doCommon2(MyLabel::staticMetaObject, ui->lineEdit->text());
    }
    else
    {
        doCommon2(MyLineEdit::staticMetaObject, ui->lineEdit->text());
    }
}

