#ifndef LOGGERPROXY_H
#define LOGGERPROXY_H

#include <QObject>

#include <src/bend/dao/logs/basiclogger.h>
#include "src/config/global.h"
using namespace GLOBAL;

class LoggerProxy : public QObject
{
    Q_OBJECT
public:
    explicit LoggerProxy(QObject *parent = nullptr);
    ~LoggerProxy();

    const LoggerProxy& reset(const QString& file, int line, const QString& func);

    //不能打印的信息，如密码
    void total(const QVariant& var, bool up=false) const; //var可以是各种可打印类型，如字符串、数字、集合、列表等，up表示是否上传
    //调试程序时打印
    void debug(const QVariant& var, bool up=false) const;
    //普通信息打印
    void info(const QVariant& var, bool up=false) const;
    //警告信息打印，但不影响执行
    void warning(const QVariant& var, bool up=false) const;
    //用户错误类信息打印
    void error(const QVariant& var, bool up=true) const;
    //致命或系统类错误打印
    void fatal(const QVariant& var, bool up=true) const;

    void setLevel(LOG_LEVEL newLevel);
    void setLogger(BasicLogger* newLogger);

signals:
    void logSig(const QString& file, int line, const QString& func, void* tid,
                int level, const QVariant& var, bool up) const;

private:
    void doLog(LOG_LEVEL level, const QVariant& var, bool up) const;

private:
    BasicLogger* m_logger = nullptr;
    LOG_LEVEL m_level;

    QString m_file;
    int m_line;
    QString m_func;
};

#endif // LOGGERPROXY_H
