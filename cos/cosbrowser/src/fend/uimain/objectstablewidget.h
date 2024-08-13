#ifndef OBJECTSWIDGET_H
#define OBJECTSWIDGET_H

#include <QWidget>

#include <src/middle/models/cloudmodels.h>

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
    void on_tableView_doubleClicked(const QModelIndex &index);
    void onObjectsSuccess(const QList<MyObject>& objects);
    void onPathChanged(const QString& newPath);
    void onPageNumChanged(int start, int maxLen);

private:
    Ui::ObjectsWidget *ui;
};

#endif // OBJECTSWIDGET_H
