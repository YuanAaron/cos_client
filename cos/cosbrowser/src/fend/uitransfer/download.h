#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QJsonValue>
#include <QWidget>

#include <src/fend/uicommon/progresswidget.h>

namespace Ui {
class Download;
}

class Download : public QWidget
{
    Q_OBJECT

public:
    explicit Download(QWidget *parent = nullptr);
    ~Download();

    void onStartDownload(const QString& jobId, const QString& key, const QString& localPath, qulonglong total);
    void onDownloadProcess(const QString& jobId, qulonglong transferedSize, qulonglong totalSize);
    void onDownloadSuccess(const QString& jobId);
    void onError(int api, const QString &msg, const QJsonValue &req);

private:
    ProgressWidget *findTableWidgetItem(const QString& jobId);
    void initHeader();
private:
    Ui::Download *ui;
};

#endif // DOWNLOAD_H
