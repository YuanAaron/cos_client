﻿#include "mylineedit.h"

#include <QDebug>
#include <QKeyEvent>

MyLineEdit::MyLineEdit(QWidget* parent)
        :QLineEdit(parent)
{

}

void MyLineEdit::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "MyLineEdit keyPressEvent";
    QLineEdit::keyPressEvent(event);
    event->ignore(); //将事件向外传递，而event->accept();是阻止事件向外传递
}

//控件的event函数先于该控件的keyPressEvent函数执行
bool MyLineEdit::event(QEvent *e)
{
    if(e->type() == QEvent::KeyPress)
    {
        qDebug() << "MyLineEdit event";
    }
    return QLineEdit::event(e);
}
