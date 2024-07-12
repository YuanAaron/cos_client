#ifndef CONFIG_H
#define CONFIG_H

#include <src/helper/filehelper.h>
#include <QString>
#include <QDir>

namespace CONFIG {
    namespace PATH {
        static const QString WORK = QDir::currentPath();
        static const QString TMP = FileHelper::joinPath(WORK,"tmp");
    }

    namespace SQLITE {
        static const QString NAME = FileHelper::joinPath(PATH::TMP,"my.db");
    }

    namespace SQL {
        static const QString LOGIN_INFO_TABLE = ":/static/sql/login_info.sql";
    }

    namespace TABLES {
        static const QString LOGIN_INFO = "login_info";
    }

    static bool init()
    {
        return FileHelper::mkPath(PATH::TMP);
    }
    static bool OK = init(); //在main函数前执行
}

#endif // CONFIG_H
