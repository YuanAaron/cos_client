#ifndef BUCKETSWIDGET_H
#define BUCKETSWIDGET_H

#include <QWidget>

namespace Ui {
class BucketsWidget;
}

class BucketsListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BucketsListWidget(QWidget *parent = nullptr);
    ~BucketsListWidget();

private:
    Ui::BucketsWidget *ui;
};

#endif // BUCKETSWIDGET_H
