#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void doCommon(const QMetaObject& obj);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    void doCommon2(const QMetaObject &obj, const QString &text);
};
#endif // WIDGET_H
