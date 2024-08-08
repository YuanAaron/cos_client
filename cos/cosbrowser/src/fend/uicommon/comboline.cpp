#include "comboline.h"

#include <QCompleter>
#include <QAbstractItemView>

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
    completer->popup()->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    completer->popup()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
