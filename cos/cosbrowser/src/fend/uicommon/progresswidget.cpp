#include "progresswidget.h"
#include "ui_progresswidget.h"

#include <QDebug>

#include <src/helper/bytehelper.h>

ProgressWidget::ProgressWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgressWidget)
{
    ui->setupUi(this);
}

ProgressWidget::~ProgressWidget()
{
    delete ui;
    qDebug() << "delete ProgressWidget";
}

void ProgressWidget::setRange(qulonglong minValue, qulonglong maxValue)
{
    m_time.restart();
    ui->progressBar->setRange(minValue, maxValue);
    ui->progressBar->setValue(0);
}

void ProgressWidget::setValue(qulonglong value)
{
    double seconds = m_time.elapsed()/1000.0; // 已经过去的时间
    ui->progressBar->setValue(value);

    static qulonglong lastValue = 0; // 上一次设置值时的上传或下载的字节数
    lastValue = value - lastValue;
    double speed = lastValue/seconds;
    QString speedStr = ByteHelper::toBeautifulStr(speed);
    ui->labelSpeed->setText(speedStr+"/s");

    int leftValue = ui->progressBar->maximum()-value; // 未下载的字节数
    if (speed > 0 && leftValue > 0)
    {
        int time = leftValue/speed;
        ui->labelTime->setText(QString::fromLocal8Bit("剩余%1s").arg(time));
    }
    else
    {
        ui->labelTime->setText("");
    }
}

void ProgressWidget::stop()
{
    m_time.invalidate();
    ui->labelSpeed->clear();
}

void ProgressWidget::setFinished(const QString &msg)
{
    setValue(ui->progressBar->maximum());
    ui->labelTime->setText(msg);
    stop();
}

void ProgressWidget::setError(const QString &msg)
{
    stop();
    ui->labelTime->setText(msg);
}
