#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QString>

class FileHelper
{
public:
    FileHelper();

    static QString readAllTxt(const QString& filePath);
};

#endif // FILEHELPER_H
