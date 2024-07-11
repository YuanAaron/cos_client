#include "filehelper.h"

#include <QFile>
#include <QJsonDocument>
#include <QDir>

FileHelper::FileHelper()
{

}

QString FileHelper::readAllTxt(const QString &filePath)
{
    QFile file(filePath);
    if (file.exists() && file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll(); //TODO QByteArray赋值给QString?
        file.close();
        return data;
    }
    throw "读取文件失败";
}

QVariant FileHelper::readAllJson(const QString &filePath)
{
    QString data = FileHelper::readAllTxt(filePath);

    QJsonDocument doc = QJsonDocument::fromJson(data.toLocal8Bit());
    return doc.toVariant();
}

QString FileHelper::joinPath(const QString &path1, const QString &path2)
{
    QString path = path1 + "/" + path2;
    QStringList pathList = path.split(QRegExp("[/\\\\]"), Qt::SkipEmptyParts); //按照/和\将路径拆分，并忽略空元素
    path = pathList.join("/");
    return QDir::cleanPath(path); //"C://abc/./../def" -> "C:/def"
}

bool FileHelper::mkPath(const QString &path)
{
    QDir dir;
    return dir.mkpath(path);
}

