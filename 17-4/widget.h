#ifndef WIDGET_H
#define WIDGET_H

#include "usermanager.h"

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

signals:
    void searchBasic();
    void searchJob();

private slots:
    void on_btnSearchBasic_clicked();
    void on_btnSearchJob_clicked();

public slots:
    void onSearchBasicFinished(const QString& name);
    void onSearchJobFinished(const QString& name);

private:
    Ui::Widget *ui;
    UserManager* manager;
};
#endif // WIDGET_H
