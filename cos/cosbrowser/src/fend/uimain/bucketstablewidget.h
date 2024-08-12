#ifndef BUCKETSTABLEWIDGET_H
#define BUCKETSTABLEWIDGET_H

#include <QWidget>

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

private:
    Ui::BucketsTableWidget *ui;
};

#endif // BUCKETSTABLEWIDGET_H
