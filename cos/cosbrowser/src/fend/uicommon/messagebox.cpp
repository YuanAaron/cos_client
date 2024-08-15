#include "messagebox.h"
#include "ui_messagebox.h"

#include <QDebug>
#include <QPushButton>

MessageBox::MessageBox(QWidget *parent) :
    CosDialog(parent),
    ui(new Ui::MessageBox)
{
    ui->setupUi(body());
    resize(350, 50);
}

MessageBox::~MessageBox()
{
    delete ui;
    qDebug() << "delete MessageBox";
}

QString MessageBox::showMessage(const QString &title, const QString &text, const QStringList& btnTextList)
{
    m_text = "";
    setTitle(title);
    ui->label->setText(text);
    createBtns(btnTextList);
    exec(); //弹出窗口
    return m_text;
}

void MessageBox::createBtns(const QStringList &textList)
{
    for(const auto& text: qAsConst(textList)) {
        QPushButton* btn = new QPushButton(text,this);
        btn->setText(text);
        connect(btn, &QPushButton::clicked, [=]() {
            m_text = text;
            accept();
        });
        ui->horizontalLayout->addWidget(btn);
    }
}
