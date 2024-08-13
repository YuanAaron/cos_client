#ifndef BUCKETSWIDGET_H
#define BUCKETSWIDGET_H

#include <QWidget>

#include <src/middle/models/cloudmodels.h>

namespace Ui {
class BucketsWidget;
}

class BucketsListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BucketsListWidget(QWidget *parent = nullptr);
    ~BucketsListWidget();

private slots:
    void on_listView_doubleClicked(const QModelIndex &index);
    void showBucketObjects(const QString& bucketName);
    void onBucketsSuccess(const QList<MyBucket>& buckets);
    void onTextEdited(const QString& text);

private:
    Ui::BucketsWidget *ui;
};

#endif // BUCKETSWIDGET_H
