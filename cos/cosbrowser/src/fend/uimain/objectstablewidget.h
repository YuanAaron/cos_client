#ifndef OBJECTSWIDGET_H
#define OBJECTSWIDGET_H

#include <QWidget>

namespace Ui {
class ObjectsWidget;
}

class ObjectsTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ObjectsTableWidget(QWidget *parent = nullptr);
    ~ObjectsTableWidget();

private slots:
    void on_btnBuckets_clicked();

private:
    Ui::ObjectsWidget *ui;
};

#endif // OBJECTSWIDGET_H
