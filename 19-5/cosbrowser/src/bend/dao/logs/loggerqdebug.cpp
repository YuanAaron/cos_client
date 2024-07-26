#include "loggerqdebug.h"

#include <QDateTime>
#include "src/config/global.h"
#include <QDebug>
#include <iostream>

LoggerQDebug::LoggerQDebug(QObject* parent)
{
    qInstallMessageHandler(handle);
}

LoggerQDebug::~LoggerQDebug()
{

}

void LoggerQDebug::print(const QString &file, int line, const QString &func, void *tid, int level, const QVariant &var, bool up)
{
    QDateTime dt;
    QString dtStr = dt.currentDateTime().toString(Qt::ISODate);
    QString front = QString::fromLocal8Bit("%1[%2]%3:%4 -")
            .arg(dtStr,GLOBAL::LOG_NAMES[level], file)
            .arg(line);
//    qDebug() << front.toLocal8Bit().data() << var;
    front = front.replace("..\\","");
    qDebug() << front.toLocal8Bit().data() << var; //使用qDebug而不是直接存文件，是为了打印QVariant类型
}

void LoggerQDebug::handle(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QFile file(filePath());

    QString key("QVariant(");
    int index = msg.indexOf(key);
    QString message = msg;
    if(index != -1)
    {
        message.replace(index, key.size(), "").chop(1);
    }

    if(file.open(QIODevice::WriteOnly|QIODevice::Append))
    {
        //输入到文件流中
        QTextStream stream(&file);
        stream << message <<endl;
        file.close();
    }
    //用于控制台输出
    std::cout << message.toLocal8Bit().data() << std::endl;
}
