#include <QCoreApplication>

#include <QDebug>
#include <QDir>
#include <QTime>
#include <QJsonObject>
#include <QJsonDocument>

QJsonObject read(const QString& path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    return doc.object();
}

void write(const QJsonObject& obj, const QString& path)
{
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    QJsonDocument doc(obj);
    file.write(doc.toJson());
    file.close();
}

QList<QStringList> readExcel()
{
    QList<QStringList> table;
    QStringList row1;
    QStringList row2;
    QStringList row3;
    row1 << "11" << "12" << "13";
    row2 << "21" << "22" << "23";
    row3 << "31" << "32" << "33";
    table << row1 << row2 << row3;
    qDebug() << table;
    return table;
}

QString readCellText(const QList<QStringList>& table, const QVariant& location)
{
    int row = -1;
    int col = -1;
    if(location.canConvert<QString>())
    {
        //A1 C2
        QString loc = location.toString();
        QString cols = "ABC"; //简化
        col = cols.indexOf(loc.at(0));
        row = loc.at(1).digitValue()-1;
    }
    else if(location.canConvert<QPoint>())
    {
        QPoint point = location.toPoint();
        row = point.x();
        col = point.y();
    }
    else
    {
        qDebug() <<  "invalid location: " << location;
        return "";
    }
    return table[row][col];
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*第一部分编码*/
    //分别测试：源文件为utf-8 with bom，ANSI(GBK)，utf-8三种情况
//    QString s1 = "ab中文";
//    qDebug() << "s1: " << s1;
//    QString s2 = QString::fromLocal8Bit("ab中文");
//    qDebug() << "s2: " << s2;
//    QString s3 = QString::fromUtf8("ab中文");
//    qDebug() << "s3: " << s3;


    /*第二部分 案例*/
    // 1 trimmed 删除两边空白字符
    //qDebug() << QString("   abcd   \n ") << QString("   abcd   \n ").trimmed();

    // 2 simplified 删除两边空白字符，同时删除中间多余的空白符，只保留一个空格
    //qDebug() << QString("   ab     \n   cd   \n ") << QString("   ab     \n   cd   \n ").simplified();

    // 3 arg格式化
    // 3.1 按照时间生成一个日志文件路径 格式为：根目录/logs/时间.log
//    QString rootDir = QDir::currentPath();
//    QString time = QTime::currentTime().toString("hh-mm-ss");
//    QString filePath = QString("%1/logs/%2.log").arg(rootDir, time);
//    qDebug() << filePath; //"C:/Users/oshacker/Documents/qt/build-13-2-Desktop_Qt_5_14_2_MSVC2015_64bit-Debug/logs/22-29-28.log"

    // 3.2 格式化数字字符串，保留2位有效数字
    //qDebug() << QString("%1").arg(123.45678, 0, 'f', 2);

    // 4 合并与拆分
    // 4.1 拼接文件路径 QStringList::join
//    QStringList sList;
//    sList << "resource" << "images" << "png" << "hello.png";
//    qDebug() << sList.join("/");

    // 4.2 获取文件名称 split
//    QString filePath = "resource/images/png/hello.png";
//    QStringList nameArray = filePath.split("/");
//    qDebug() << nameArray;
//    qDebug() << nameArray.last();

    // 4.2 获取文件名称 section
//    qDebug() << filePath.section("/", -1);

    //13-3：编写excel读取单元格的接口
//    QList<QStringList> table = readExcel();
//    qDebug() << "String:" << readCellText(table, "C2");
//    qDebug() << "Point:" << readCellText(table, QPoint(1,2));

    //13-4
    QJsonObject object = read("C:/Users/oshacker/Documents/qt/13-2/read.json");
    qDebug() << object;
    object["object"] = "new string";
    write(object, "C:/Users/oshacker/Documents/qt/13-2/write.json");
    return a.exec();
}
