#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    Q_INVOKABLE MyLabel(QWidget* parent=nullptr);
};

#endif // MYLABEL_H
