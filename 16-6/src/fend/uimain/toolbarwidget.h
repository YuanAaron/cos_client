#ifndef TOOLBARWIDGET_H
#define TOOLBARWIDGET_H

#include <QWidget>

namespace Ui {
class ToolbarWidget;
}

class ToolbarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToolbarWidget(QWidget *parent = nullptr);
    ~ToolbarWidget();

signals:
//    void quitLogin();

    //不使用QSignalMapper的情况下，工具栏按钮与uimain中组件的交互
//    void refreshSig();

    void btnClicked(const QString& text);

private slots:
    void on_btnUpload_clicked();

    void on_btnDownload_clicked();

private:
    Ui::ToolbarWidget *ui;
};

#endif // TOOLBARWIDGET_H
