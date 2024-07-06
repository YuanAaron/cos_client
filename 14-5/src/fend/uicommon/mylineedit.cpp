#include "mylineedit.h"

#include <QKeyEvent>

MyLineEdit::MyLineEdit(QWidget* parent)
        :QLineEdit(parent)
{

}

void MyLineEdit::keyPressEvent(QKeyEvent *e)
{
    //捕获Ctrl+C和Ctrl+V
    if(e->modifiers() == Qt::ControlModifier)
    {
        if(e->key() == Qt::Key_C || e->key() == Qt::Key_V)
        {
            return;
        }
    }
    QLineEdit::keyPressEvent(e);
}
