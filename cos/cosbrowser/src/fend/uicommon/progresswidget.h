#ifndef PROGRESSWIDGET_H
#define PROGRESSWIDGET_H

#include <QElapsedTimer>
#include <QWidget>

namespace Ui {
class ProgressWidget;
}

class ProgressWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressWidget(QWidget *parent = nullptr);
    ~ProgressWidget();

    void setRange(qulonglong minValue, qulonglong maxValue);
    void setValue(qulonglong value);
    void stop();
    void setFinished(const QString& msg);
    void setError(const QString& msg);

private:
    Ui::ProgressWidget *ui;
    QElapsedTimer m_time;
};

#endif // PROGRESSWIDGET_H
