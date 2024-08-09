#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H

#include <QWidget>

namespace Ui {
class PageWidget;
}

class PageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PageWidget(QWidget *parent = nullptr);
    ~PageWidget();

    //获取属性值
    int totalRow() const;
    int maxRow() const;
    int currentPage() const;
    int pageCount() const;
    int isFirstPage() const;
    int isLastPage() const;

    //设置属性值
    void setTotalRow(int newTotalRow);
    void setMaxRow(int rows); //设置当前页最大显示行数
    void setMaxRowList(const QList<int> rowList);   //设置单页显示行数选择列表(初始化部分）

signals:
    /**
     * @brief pageNumChanged 当页码发生变化时发出信号
     * @param start 起始索引
     * @param maxLen 每页最大条数
     */
    void pageNumChanged(int start, int maxLen);

public slots:
    void next();
    void pre();
    void jumpTo(int page);

private slots:
    void onCurrentPageSelected(const QString &text);
    void onMaxRowsItemSelected(const QString &text);

private:
    void reset();                           // 重置为首页
    void setPageCount();                    // 设置页号选择列表(初始化部分）
    void switchPage(int newCurrentPage);    // 切换页码

private:
    Ui::PageWidget *ui;
    int m_totalRow = 0; //总行数
    int m_maxRow = 10; //每页多少行
    int m_currentPage = 1; //当前是第几页
};

#endif // PAGEWIDGET_H
