#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QLineEdit>
#include <QMetaProperty>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->label->setProperty("newProperty","propertyVal");

    const QMetaObject* meta = ui->label_3->metaObject();
    int cnt = meta->propertyCount();
    for (int i=0; i < cnt; i++) {
        QString name= meta->property(i).name();
        QString value = ui->label_3->property(name.toLocal8Bit().data()).toString();
        QLineEdit* edit = new QLineEdit(value);
        edit->setProperty("customName",name);
//        edit->setProperty("customVal",value);
        connect(edit, SIGNAL(editingFinished()), this, SLOT(onFinished()));
        ui->formLayout->addRow(name,edit);
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    //动态属性
    qDebug() << ui->label->property("newProperty");
    qDebug() << ui->label->property("newProperty");
    //静态属性
    qDebug() << ui->label_2->property("text");
    //修改静态属性的值，啥意思？
    ui->label_2->setProperty("text","hello");
}

void Widget::onFinished()
{
    QLineEdit* edit = dynamic_cast<QLineEdit*>(sender());
    QString name = edit->property("customName").toString();

//    QVariant v = edit->property("customVal");
//    QVariant value;
//    if(v.type() == QVariant::Int)
//    {
//        value.setValue(edit->text().toInt());
//    }
//    else
//    {
//        value.setValue(edit->text());
//    }

//    ui->label_3->setProperty(name.toLocal8Bit().data(),value);

    //不转换，好像也OK
    ui->label_3->setProperty(name.toLocal8Bit().data(),edit->text());
}
