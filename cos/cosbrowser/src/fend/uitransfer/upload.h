#ifndef UPLOAD_H
#define UPLOAD_H

#include <QJsonValue>
#include <QWidget>

#include <src/fend/uicommon/progresswidget.h>

namespace Ui {
class Upload;
}

class Upload : public QWidget
{
    Q_OBJECT

public:
    explicit Upload(QWidget *parent = nullptr);
    ~Upload();

private slots:
    void onStartUpload(const QString& jobId, const QString& key, const QString& localPath);
    void onUploadProcess(const QString& jobId, qulonglong transferedSize, qulonglong totalSize);
    void onUploadSuccess(const QString& jobId);
    void onError(int api, const QString& msg, const QJsonValue &req);

private:
    ProgressWidget* findTableWidgetItem(const QString& jobId);
    void initHeader();

private:
    Ui::Upload *ui;
};

#endif // UPLOAD_H
