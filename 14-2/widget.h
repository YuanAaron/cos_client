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

    void renameFile();

signals:
    void downloadFile();

private slots:
    void on_pushButton_clicked();

    void onDownloadFile1();
    void onDownloadFile2();
    void onDownloadFile3();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
