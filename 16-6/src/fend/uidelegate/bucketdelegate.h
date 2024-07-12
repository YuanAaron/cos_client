#ifndef BUCKETDELEGATE_H
#define BUCKETDELEGATE_H

#include <QStyledItemDelegate>

class BucketDelegate : public QStyledItemDelegate
{
public:
    BucketDelegate(QObject* parent = nullptr);

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;

protected slots:
    void print(QObject* obj);

};

#endif // BUCKETDELEGATE_H
