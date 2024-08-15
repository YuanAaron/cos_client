#include "tableitemdelegate.h"

TableItemDelegate::TableItemDelegate(QAbstractItemView* table, QObject* parent)
            :QStyledItemDelegate(parent),m_table(table)
{

}

void TableItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //鼠标悬停且索引有效
    if(option.state.testFlag(QStyle::State_MouseOver) && index.isValid())
    {
        QAbstractItemModel* m = m_table->model();
        int row =index.row();
        int columnCount = m->columnCount();
        //遍历第row行中的所有列
        for(int i = 0; i < columnCount; i++)
        {
            QModelIndex idx = m->index(row, i);
            QStyleOptionViewItem op = option;
            op.index = idx;
            op.rect = m_table->visualRect(idx);
            QStyledItemDelegate::paint(painter, op, idx);
        }
        return ;
    }

    return QStyledItemDelegate::paint(painter, option, index);
}
