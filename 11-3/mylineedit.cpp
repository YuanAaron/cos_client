#include "mylineedit.h"

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
    event->ignore();
}
