#include "pushbutton.h"

PushButton::PushButton(QWidget* parent)
        :QPushButton(parent)
{

}

void PushButton::enterEvent(QEvent *event)
{
    setCursor(Qt::PointingHandCursor);
}

void PushButton::leaveEvent(QEvent *event)
{
    setCursor(Qt::ArrowCursor);
}
