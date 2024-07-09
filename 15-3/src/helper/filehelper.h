#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QString>
#include <QVariant>

class FileHelper
{
public:
    FileHelper();

    static QString readAllTxt(const QString& filePath);
    static QVariant readAllJson(const QString& filePath);
};

#endif // FILEHELPER_H
