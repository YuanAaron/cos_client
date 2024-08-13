#ifndef BUCKETSTABLEWIDGET_H
#define BUCKETSTABLEWIDGET_H

#include <QWidget>

#include <src/middle/models/cloudmodels.h>

namespace Ui {
class BucketsTableWidget;
}

class BucketsTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BucketsTableWidget(QWidget *parent = nullptr);
    ~BucketsTableWidget();

private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);
    void onPageNumChanged(int start, int maxLen);
    void onBucketsSuccess(const QList<MyBucket>& buckets);

    void on_btnCreateBucket_clicked();

private:
    Ui::BucketsTableWidget *ui;
};

#endif // BUCKETSTABLEWIDGET_H
