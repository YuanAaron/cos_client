#include "basedialog.h"
#include "ui_basedialog.h"

#include <QDebug>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPushButton>
#include <QKeyEvent>

BaseDialog::BaseDialog(QWidget *parent)
    : QDialog(parent)
    , m_ui(new Ui::BaseDialog)
{
    m_ui->setupUi(this);
    //设置窗口无标题栏
    this->setWindowFlags(Qt::CustomizeWindowHint);
    //设置图标
    setLogo(":/static/imgs/qtlogo.png");
    m_ui->labelLogo->setFixedSize(28, 28);

    addCloseButton(":/static/imgs/Close-1.png",":/static/imgs/Close-2.png");

    setAllButtonSize();
}

BaseDialog::~BaseDialog()
{
    delete m_ui;
    qDebug() << "delete BaseDialog";
}

void BaseDialog::setTitle(const QString &title)
{
    m_ui->labelTitle->setText(title);
}

void BaseDialog::setLogo(const QString &path)
{
    m_ui->labelLogo->setStyleSheet(QString("border-image: url(\"%1\");").arg(path));
}

void BaseDialog::addMinButton(const QString &path, const QString &hoverPath)
{
    QPushButton* btn = addButton(path, hoverPath);
    connect(btn, &QPushButton::clicked, this, &BaseDialog::showMinimized);
}

void BaseDialog::addMaxButton(const QString &maxPath, const QString &maxPathHover, const QString &normalPath, const QString &normalPathHover)
{
    QPushButton* btn = addButton(maxPath, maxPathHover);

    auto funcImg = [=]() {
        isMaximized() ? setButtonImage(btn, normalPath, normalPathHover)
                      : setButtonImage(btn, maxPath, maxPathHover);
    };
    auto funcShow  = [=]() {
        isMaximized() ? showNormal() : showMaximized();
        funcImg();
    };

    connect(btn, &QPushButton::clicked, this, funcShow);
    funcImg();
}

QPushButton *BaseDialog::addButton(const QString &path, const QString &hoverPath)
{
    QPushButton* btn = new QPushButton;
//    btn->setFixedSize(m_sz, m_sz);
    setButtonImage(btn, path, hoverPath);
    int i = m_ui->horizontalLayout->indexOf(m_ui->btnClose);
    m_ui->horizontalLayout->insertWidget(i, btn);
    return btn;
}

void BaseDialog::setButtonImage(QPushButton *btn, const QString &path, const QString &hoverPath)
{
    btn->setStyleSheet(QString(
        "QPushButton{border-image: url(\"%1\");}"
        "QPushButton:hover{border-image: url(\"%2\");}"
        ).arg(path, hoverPath));
}

void BaseDialog::setAllButtonSize(int w)
{
    QList<QPushButton *> btnList = m_ui->frameTitle->findChildren<QPushButton*>();
    for (auto* btn: btnList) {
        btn->setFixedSize(w, w);
    }
//    m_sz = w;
}

void BaseDialog::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        m_start = e->pos(); // 相对于父控件坐标原点的位置
    }
    QDialog::mousePressEvent(e);

}

void BaseDialog::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        QPoint targetPos = e->pos()-m_start+pos();
        this->move(targetPos);
    }
    QDialog::mouseMoveEvent(e);
}

QWidget *BaseDialog::body()
{
    return m_ui->widgetBody;
}

void BaseDialog::addCloseButton(const QString &path, const QString &hoverPath)
{
    setButtonImage(m_ui->btnClose, path, hoverPath);
    m_ui->horizontalLayout->addWidget(m_ui->btnClose);
    connect(m_ui->btnClose, &QPushButton::clicked, this, &BaseDialog::reject);
}
