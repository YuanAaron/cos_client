#ifndef CONFIG_H
#define CONFIG_H

#include <src/helper/filehelper.h>
#include <QString>
#include <QDir>

namespace GLOBAL {
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

    namespace VERSION {
        static const QString MAJOR_CUSTOM = "custom";
        static const QString MAJOR_BUSINESS = "business";
        static const QString JSON_PATH = ":/static/versions/config_default.json";
    }

    namespace ENV {
        static const QString ENV_DEV = "dev";
        static const QString ENV_ALPHA = "alpha";
        static const QString ENV_BETA = "beta";
        static const QString ENV_PRE = "pre";
        static const QString ENV_PROD = "prod";
    }

    static bool init()
    {
        return FileHelper::mkPath(PATH::TMP);
    }
//    static bool OK = init(); //在main函数前执行
}

#endif // CONFIG_H
