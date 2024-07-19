#include "widget.h"
#include "ui_widget.h"

#include <QDir>
#include <QFileDialog>
#include <QTime>
#include <QtConcurrent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnBrowser_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(this,QString::fromLocal8Bit("选择目录"));
    ui->lineEdit->setText(dirPath);
}

void Widget::on_btnCalc_clicked()
{
    QString dirPath= ui->lineEdit->text();
    QStringList files = findFiles(dirPath);

    QTime time;
    time.start();
    //使用单线程统计代码行数
    int res = totalCount(files);
    ui->textEdit->append(QString::fromLocal8Bit("使用单线程统计结果：总行数%1，总耗时%2ms").arg(res).arg(time.elapsed()));

    //使用多线程统计代码行数（为什么时间反而长呢？）
    time.restart();
    //使用多线程统计代码行数
    res = concurrentTotalCount(files);
    ui->textEdit->append(QString::fromLocal8Bit("使用多线程统计结果：总行数%1，总耗时%2ms").arg(res).arg(time.elapsed()));
}

QStringList Widget::findFiles(const QString &dirPath)
{
    //待查找的所有*.h和*.cpp的文件
    QStringList names;

    QStringList filters;
    filters << "*.h" << "*.cpp";

    QDir dir(dirPath);
    //foreach是Qt增加的关键字
    foreach(QString file, dir.entryList(filters, QDir::Files))
    {
        names += dirPath + "/" + file; //+= ？？？
    }

    foreach(QString subDir, dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot))
    {
        names += findFiles(dirPath + "/" + subDir);
    }

    return names;
}

int Widget::totalCount(const QStringList &fileList)
{
    int total = 0;
    for(auto file: fileList)
    {
        total += perCount(file);
    }
    return total;
}

int Widget::perCount(const QString &path)
{
    //每个文件的代码行数
    int total =0;
    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        while(!file.atEnd())
        {
            file.readLine();
            total++;
        }
    }
    return total;
}

int Widget::concurrentTotalCount(const QStringList &fileList)
{
    int total = QtConcurrent::mappedReduced(
                    fileList,
                    perCount, //单个处理函数
                    sumCount //汇总函数
                );
    return total;
}

void Widget::sumCount(int &res, int count)
{
    res += count;
}
