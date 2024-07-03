#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>
#include <QWidget>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    MyLineEdit(QWidget* parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event);
    bool event(QEvent *e);
};

#endif // MYLINEEDIT_H
