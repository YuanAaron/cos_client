#include "basiclogger.h"

#include <QDate>

#include <src/helper/filehelper.h>
#include "src/config/global.h"

BasicLogger::BasicLogger(QObject* parent)
{
    m_td = new QThread();
    moveToThread(m_td);
    m_td->start();
}

BasicLogger::~BasicLogger()
{
    if(m_td->isRunning())
    {
        m_td->quit();
        if(m_td->wait(1000))
        {
            m_td->terminate();
            m_td->wait(1000);
        }
    }
    delete m_td;
}

void BasicLogger::onLog(const QString &file, int line, const QString &func, void *tid, int level, const QVariant &var, bool up)
{
    print(file, line, func, tid, level, var, up);
}

QString BasicLogger::filePath()
{
    QString name = QDate::currentDate().toString(Qt::ISODate);
    return FileHelper::joinPath(GLOBAL::PATH::LOG_DIR, QString::fromLocal8Bit("%1.log").arg(name)); //日志文件命名一般以天为单位
}
