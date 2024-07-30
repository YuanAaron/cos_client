#ifndef MANGLOBAL_H
#define MANGLOBAL_H

#include <QObject>
#include "src/config/loggerproxy.h"

#define MLOG MG->m_log
#define mTotal MLOG->reset(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).total
#define mDebug MLOG->reset(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).debug
#define mInfo MLOG->reset(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).info
#define mWarning MLOG->reset(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).warning
#define mError MLOG->reset(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).error
#define mFatal MLOG->reset(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).fatal

#define MG ManagerGlobal::instance()

//不能将其他单例类的头文件放在全局单例的头文件中（包含了日志类的头文件，因为日志类头文件基本每个类都会使用）
//而是具体哪个类引用了，哪个类再包含
class ManagerCloud;
class ManagerDB;
class ManagerPlugin;
class LoggerProxy;
class GateWay;
class ManagerSignals;
class ManagerModel;

class ManagerGlobal : public QObject
{
    Q_OBJECT
public:
    explicit ManagerGlobal(QObject *parent = nullptr);
    ~ManagerGlobal();
    static ManagerGlobal* instance();

    void init(int argc, char* argv[]);

public:
    ManagerCloud* m_cloud = nullptr;
    ManagerDB* m_db = nullptr;
    ManagerPlugin* m_plugin = nullptr;
    LoggerProxy* m_log = nullptr;
    GateWay* m_gate = nullptr;
    ManagerSignals* m_signal = nullptr;
    ManagerModel* m_model = nullptr;
};

#endif // MANGLOBAL_H
