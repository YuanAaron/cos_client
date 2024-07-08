#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    Q_INVOKABLE MyLineEdit(QWidget* parent=nullptr);
};

#endif // MYLINEEDIT_H
