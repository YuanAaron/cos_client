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

    static QString joinPath(const QString& path1, const QString& path2);
    static bool mkPath(const QString& path);

    static QList<QStringList> readAllCsv(const QString& filePath);
    static void writeFile(const QStringList lines, const QString& filePath);
};

#endif // FILEHELPER_H
