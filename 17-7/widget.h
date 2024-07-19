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

private slots:
    void on_btnBrowser_clicked();
    void on_btnCalc_clicked();

private:
    QStringList findFiles(const QString& dirPath);

    int totalCount(const QStringList& fileList);
    static int perCount(const QString& path);

    int concurrentTotalCount(const QStringList& fileList);
    static void sumCount(int& res, int count);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
