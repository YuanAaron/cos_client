#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>

class PushButton : public QPushButton
{
    Q_OBJECT
public:
    PushButton(QWidget* parent = nullptr);

protected:
    virtual void enterEvent(QEvent* event) override;
    virtual void leaveEvent(QEvent* event) override;
};

#endif // PUSHBUTTON_H
