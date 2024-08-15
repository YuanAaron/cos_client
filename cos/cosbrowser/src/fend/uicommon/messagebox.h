#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include "cosdialog.h"

#include <QWidget>

namespace Ui {
class MessageBox;
}

class MessageBox : public CosDialog
{
    Q_OBJECT

public:
    explicit MessageBox(QWidget *parent = nullptr);
    ~MessageBox();

    QString showMessage(const QString& title,
                        const QString& text,
                        const QStringList &btnTextList = QStringList(QString::fromLocal8Bit("确定")));

private:
    void createBtns(const QStringList& textList);

private:
    Ui::MessageBox *ui;
    QString m_text;
};

#endif // MESSAGEBOX_H
