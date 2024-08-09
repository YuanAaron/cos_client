#include "pagewidget.h"
#include "ui_pagewidget.h"

#include <QDebug>
#include <QtMath>

PageWidget::PageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageWidget)
{
    ui->setupUi(this);

    connect(ui->btnNext, &QPushButton::clicked, this, &PageWidget::next);
    connect(ui->btnPre, &QPushButton::clicked, this, &PageWidget::pre);

    ui->lineMaxRows->setAlignment(Qt::AlignHCenter);
    ui->lineMaxRows->setReadOnly(true);
    connect(ui->lineMaxRows, &ComboLine::itemSelected, this, &PageWidget::onMaxRowsItemSelected);
    ui->lineCurrentPage->setAlignment(Qt::AlignHCenter);
    ui->lineCurrentPage->setReadOnly(true);
    connect(ui->lineCurrentPage, &ComboLine::itemSelected, this, &PageWidget::onCurrentPageSelected);

    ui->btnNext->setDisabled(true);
    ui->btnPre->setDisabled(true);
}

PageWidget::~PageWidget()
{
    delete ui;
    qDebug() << "delete PageWidget";
}

int PageWidget::totalRow() const
{
    return m_totalRow;
}

int PageWidget::maxRow() const
{
    return m_maxRow;
}

int PageWidget::currentPage() const
{
    return m_currentPage;
}

int PageWidget::pageCount() const
{
    if(m_totalRow == 0)
        return 1;

    //qCeil获取不小于value的最小整数
    return qCeil(m_totalRow/float(m_maxRow));
}

int PageWidget::isFirstPage() const
{
    return currentPage() == 1;
}

int PageWidget::isLastPage() const
{
    return currentPage() == pageCount();
}

void PageWidget::setTotalRow(int newTotalRow)
{
    m_totalRow = newTotalRow;
    ui->labelTotalCount->setText(QString::fromLocal8Bit("共%1条，每页").arg(newTotalRow));
    reset();
}

void PageWidget::setMaxRow(int rows)
{
    QStringList words = ui->lineMaxRows->getWords();
    for(const QString& num: qAsConst(words))
    {
        if(num.toInt() == rows)
        {
            m_maxRow = rows;
            reset();
            break;
        }
    }
}

void PageWidget::setMaxRowList(const QList<int> rowList)
{
    ui->lineMaxRows->setWords(rowList);
    if (rowList.size() > 0) {
        ui->lineMaxRows->setText(QString::number(rowList[0]));
        setMaxRow(rowList[0]);
    }
}

void PageWidget::next()
{
    jumpTo((currentPage()+1));
}

void PageWidget::pre()
{
    jumpTo((currentPage()-1));
}

void PageWidget::jumpTo(int page)
{
    if(page != currentPage())
    {
        switchPage(page);
    }
}

void PageWidget::onCurrentPageSelected(const QString &text)
{
    if (m_currentPage != text.toInt())
        jumpTo(text.toInt());
}

void PageWidget::onMaxRowsItemSelected(const QString &text)
{
    setMaxRow(text.toInt());
}

void PageWidget::reset()
{
    setPageCount();
    switchPage(1); //重置为首页
}

void PageWidget::setPageCount()
{
    int count = pageCount();
    ui->labelPageCount->setText("/"+QString::number(count));
    ui->lineCurrentPage->setWords(1, count);
    ui->lineCurrentPage->setText("1");
}

void PageWidget::switchPage(int newCurrentPage)
{
    m_currentPage = newCurrentPage;
    ui->lineCurrentPage->setText(QString::number(newCurrentPage));
    ui->btnPre->setDisabled(isFirstPage());
    ui->btnNext->setDisabled(isLastPage());

    int start = (newCurrentPage-1)*maxRow();
    int left = totalRow()-start;
    int len = left < maxRow()?left:maxRow();
    qDebug() << QString("switchPage %1,%2").arg(start).arg(len);
    emit pageNumChanged(start, len);

}
