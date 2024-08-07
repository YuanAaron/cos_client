#include "breadwidget.h"
#include "ui_breadwidget.h"

#include <QDebug>

BreadWidget::BreadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BreadWidget)
{
    ui->setupUi(this);

    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView->setFlow(QListView::LeftToRight);
    ui->listView->setStyleSheet("QListView{border:none;}");
    ui->listView->setModel(m_model);
    setPath("");
    connect(ui->listView, &QListView::clicked, this, &BreadWidget::onItemClicked);
    setFixedHeight(30);
}

BreadWidget::~BreadWidget()
{
    delete ui;
    qDebug() << "delete BreadWidget";
}

void BreadWidget::setPath(const QString &path)
{
    setPath(path.split("/", Qt::SkipEmptyParts));
}

void BreadWidget::setPath(const QStringList &names)
{
    //传入的目录名不能为空
    if(names.size() == 0)
    {
        return;
    }
    clear();
    m_rootName = names[0];
    for(const QString& name : names)
    {
        addNameButton(name.trimmed());
    }
}

void BreadWidget::clear()
{
    m_model->clear();
}

QString BreadWidget::currentPath() const
{
    return getPath();
}

QString BreadWidget::rootName() const
{
    return m_rootName;
}

bool BreadWidget::isEmpty() const
{
    return ui->listView->model()->rowCount() == 0;
}

bool BreadWidget::isRoot() const
{
    return getPath() == m_rootName;
}

void BreadWidget::addNameButton(const QString &name)
{
    if(name == "")
        return;

    QStandardItem* item = new QStandardItem;
    item->setText(name);
    if(!isEmpty())
    {
        item->setIcon(QIcon(":/static/imgs/right.png")); //向右箭头
    }
    m_model->appendRow(item);
}

void BreadWidget::onItemClicked(const QModelIndex &index)
{
    QStandardItem* newItem = m_model->itemFromIndex(index);
    QStandardItem* oldItem = currentItem();

    if(newItem == oldItem)
    {
        QString oldPath = getPath(oldItem);
        emit refresh(oldPath);
        qDebug() << "refresh" << oldPath;
    }
    else
    {
        QString newPath = getPath(newItem);
        int idx = newItem->row();
        m_model->removeRows(idx+1, m_model->rowCount()-(idx+1));
        emit pathChanged(newPath);
        qDebug() << "pathChanged" << newPath;
    }

}

QStandardItem *BreadWidget::currentItem() const
{
    return m_model->item(m_model->rowCount()-1);
}

QString BreadWidget::getPath(QStandardItem *item) const
{
    if(!item)
        item = currentItem();

    int idx = item->row();
    QStringList pathList;
    for (int i=0; i<=idx; i++)
    {
        QStandardItem* b = m_model->item(i);
        if(b)
        {
            pathList << b->text();
        }
    }
    return pathList.join("/");
}
