#ifndef LOGGERQDEBUG_H
#define LOGGERQDEBUG_H

#include "basiclogger.h"

class LoggerQDebug : public BasicLogger
{
    Q_OBJECT
public:
    LoggerQDebug(QObject* parent = nullptr);
    ~LoggerQDebug();

protected:
    virtual void print(const QString &file, int line, const QString &func, void *tid,
                       int level, const QVariant &var, bool up) override;

private:
    //QDebug拦截器：QDebug正常情况下会打印到控制台，这里需要将信息打印到文件
    static void handle(QtMsgType type, const QMessageLogContext& context, const QString& msg);
    QThread* m_td = nullptr;
};

#endif // LOGGERQDEBUG_H
