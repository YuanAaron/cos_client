#ifndef TABLEITEMDELEGATE_H
#define TABLEITEMDELEGATE_H

#include <QAbstractItemView>
#include <QStyledItemDelegate>

class TableItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    TableItemDelegate(QAbstractItemView* table, QObject* parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QAbstractItemView* m_table; //指明被代理的View，方便获取整行的item
};

#endif // TABLEITEMDELEGATE_H
