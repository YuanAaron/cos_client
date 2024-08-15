#include "comboline.h"

#include <QCompleter>
#include <QAbstractItemView>

#include <src/fend/uidelegate/tableitemdelegate.h>

ComboLine::ComboLine(QWidget* parent)
        :QLineEdit(parent)
{
    ComboLine(QStringList(), parent);
}

ComboLine::ComboLine(const QStringList &words, QWidget *parent)
        :QLineEdit(parent)
{
    setWords(words);
}

void ComboLine::setWords(const QStringList &words)
{
    QCompleter* completer = new QCompleter(words, this);
    QAbstractItemView* view = completer->popup(); //其实是QListView
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //美化：这里的view列表其实是QListView，这样设置后view可以享有Qss中QAbstractItemView的效果、TableItemDelegate的效果以及手形鼠标的效果
    view->setItemDelegate(new TableItemDelegate(view));
    view->setCursor(Qt::PointingHandCursor);

    connect(completer, QOverload<const QString&>::of(&QCompleter::activated),
            [=](const QString& text) {
        emit itemSelected(text);
    });
    setCompleter(completer);
    completer->setFilterMode(Qt::MatchContains);
}

void ComboLine::setWords(const QList<int> words)
{
    QStringList strs;
    for(int i : words)
    {
        strs << QString::number(i);
    }
    setWords(strs);
}

void ComboLine::setWords(int start, int len)
{
    QStringList strs;
    for(int i=start; i<=len; i++)
    {
        strs << QString::number(i);
    }
    setWords(strs);
}

QStringList ComboLine::getWords()
{
    QStringList strs;
    QCompleter* com = completer();
    if(com)
    {
        QAbstractItemModel* m = com->model();
        for (int i=0; i<m->rowCount(); i++) {
            strs << m->index(i,0).data().toString();
        }
    }
    return strs;
}

void ComboLine::mousePressEvent(QMouseEvent *e)
{
    QCompleter* com = completer();
    if(com)
    {
        com->complete();
    }
    QLineEdit::mousePressEvent(e);
}
