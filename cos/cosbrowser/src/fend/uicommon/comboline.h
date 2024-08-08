#ifndef COMBOLINE_H
#define COMBOLINE_H

#include <QLineEdit>

class ComboLine : public QLineEdit
{
    Q_OBJECT
public:
    ComboLine(QWidget* parent = nullptr);
    ComboLine(const QStringList& words, QWidget* parent = nullptr);

    //设置提示列表
    void setWords(const QStringList& words);
    void setWords(const QList<int> words);
    void setWords(int start=1, int len=10);

    //获取提示列表
    QStringList getWords();

signals:
    //提示列表被选中
    void itemSelected(const QString& text);

protected:
    void mousePressEvent(QMouseEvent* e) override;
};

#endif // COMBOLINE_H
