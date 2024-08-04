#include "daocloudscos.h"

#include "src/config/exceptions.h"
#include "src/config/errorcode.h"
#include <QDebug>

#include "cos_api.h"
using namespace qcloud_cos;

DaoCloudsCos::DaoCloudsCos()
{
    // 指定配置文件路径，初始化CosConfig
    m_config = new CosConfig("./cosconfig.json");
}

DaoCloudsCos::~DaoCloudsCos()
{
    delete m_config;
    m_config = nullptr;
}

QList<MyBucket> DaoCloudsCos::buckets()
{
    QList<MyBucket> res;
    CosAPI cos = CosAPI(*m_config);

    // 构造查询存储桶列表的请求
    GetServiceReq req;
    GetServiceResp resp;
    CosResult result = cos.GetService(req, &resp);

    // 处理调用结果
    if (result.IsSucc()) {
        // 查询存储桶列表成功
        const std::vector<Bucket>& buckets = resp.GetBuckets();
        for (std::vector<Bucket>::const_iterator itr = buckets.begin(); itr != buckets.end(); ++itr) {
            const Bucket& bucket = *itr;

            MyBucket myb;
            myb.name = QString(bucket.m_name.c_str());
            myb.location = QString(bucket.m_location.c_str());
            myb.createDate = QString(bucket.m_create_date.c_str());
            res.append(myb);
        }
    } else {
        // 查询存储桶列表失败
        throwError(EC_211000, result);
    }
    return res;
}

bool DaoCloudsCos::isBucketExists(const QString &bucketName)
{
    //该种方法获取的结果并非实时，废弃
//    QString location = getBucketLocation(bucketName);
//    m_config->SetRegion(location.toLocal8Bit().data());
//    CosAPI cos = CosAPI(*m_config);
//    return cos.IsBucketExist(bucketName.toStdString());

    //使用buckets来判断存储桶是否存在
    QList<MyBucket> bs = buckets();
    for(const auto& b : qAsConst(bs))
    {
        if(b.name==bucketName)
            return true;
    }
    return false;
}

QString DaoCloudsCos::getBucketLocation(const QString &bucketName)
{
    CosAPI cos = CosAPI(*m_config);
    QString location(cos.GetBucketLocation(bucketName.toStdString()).c_str());
    if(location != "")
    {
        return location;
    }

    //为什么加下面代码？？？
    MyBucket bucket = getBucketByName(bucketName);
    if(bucket.isValid())
    {
        return bucket.location;
    }
    throw BaseException(EC_332000, QString::fromLocal8Bit("获取桶位置失败：%1").arg(bucketName));
}

void DaoCloudsCos::putBucket(const QString &bucketName, const QString &location)
{
    if(isBucketExists(bucketName))
        return;

    PutBucketReq req(bucketName.toLocal8Bit().data());
    PutBucketResp resp;
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);
    CosResult result = cos.PutBucket(req, &resp);
    if(!result.IsSucc())
    {
        throwError(EC_331100, result);
    }
}

void DaoCloudsCos::deleteBucket(const QString &bucketName)
{
    if(!isBucketExists(bucketName))
        return;

    //注意只能删除空桶
    DeleteBucketReq req(bucketName.toLocal8Bit().data());
    DeleteBucketResp resp;
    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);
    CosResult result = cos.DeleteBucket(req, &resp);
    if(!result.IsSucc())
    {
        throwError(EC_331300, result);
    }
}

QList<MyObject> DaoCloudsCos::getObjects(const QString &bucketName, const QString &dir)
{
    GetBucketResp resp;
    GetBucketReq req(bucketName.toLocal8Bit().data());
    if(dir != "")
        req.SetPrefix(dir.toLocal8Bit().data());
    req.SetDelimiter("/");

    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);
    CosResult result = cos.GetBucket(req, &resp);

    if(!result.IsSucc())
    {
        throwError(EC_331200, result);
    }
    return getDirList(resp, dir) + getFileList(resp, dir);
}

void DaoCloudsCos::putObject(const QString &bucketName, const QString &key, const QString &localPath, const TransProgressCallback &callback)
{
    //初始化上传

    //异步上传
    AsyncPutObjectReq put_req(bucketName.toLocal8Bit().data(), key.toLocal8Bit().data(), localPath.toLocal8Bit().data());
    //设置上传进度回调
    if(callback)
    {
        put_req.SetTransferProgressCallback(callback);
    }

    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);

    //开始上传对象
    SharedAsyncContext context = cos.AsyncPutObject(put_req);
    context->WaitUntilFinish(); //等待上传结束
    CosResult res = context->GetResult();
    if(!res.IsSucc())
    {
        throwError(EC_332400, res);
    }
}

void DaoCloudsCos::getObject(const QString &bucketName, const QString &key, const QString &localPath, const TransProgressCallback &callback)
{
    //下载初始化

    //异步下载
    AsyncGetObjectReq get_req(bucketName.toLocal8Bit().data(), key.toLocal8Bit().data(), localPath.toLocal8Bit().data());
    //设置下载进度回调
    if(callback)
    {
        get_req.SetTransferProgressCallback(callback);
    }

    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);

    //开始下载对象
    SharedAsyncContext context = cos.AsyncGetObject(get_req);
    context->WaitUntilFinish(); //等待下载结束
    CosResult res = context->GetResult();
    if(!res.IsSucc())
    {
        throwError(EC_332500, res);
    }
}

bool DaoCloudsCos::isObjectExists(const QString &bucketName, const QString &key)
{
    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);
    return cos.IsObjectExist(bucketName.toStdString(), key.toLocal8Bit().data());
}

QList<MyBucket> DaoCloudsCos::login(const QString &secretId, const QString &secretKey)
{
    m_config->SetAccessKey(secretId.toStdString());
    m_config->SetSecretKey(secretKey.toStdString());
    m_config->SetRegion("ap-guangzhou"); //没这个会报错
    return buckets();
}

void DaoCloudsCos::throwError(const QString &code, CosResult &result)
{
    QString msg = QString::fromLocal8Bit("腾讯云错误码 【%1】：%2")
                          .arg(result.GetErrorCode().c_str(), result.GetErrorMsg().c_str());
    throw BaseException(code, msg);
}

QList<MyObject> DaoCloudsCos::getDirList(GetBucketResp &resp, const QString &dir)
{
    QList<MyObject> res;
    //获取目录列表
    std::vector<std::string> cs = resp.GetCommonPrefixes();
    for(int i = 0; i < cs.size(); ++i){
        QString key(cs[i].c_str());
//        qDebug() << "dir: " << key;
        MyObject object;
        object.dir = dir;
        object.name = key.mid(dir.size());
        object.lastmodified = "-";
        res.append(object);
//        qDebug() << "dirName: " << object.name;
    }
    return res;
}

QList<MyObject> DaoCloudsCos::getFileList(GetBucketResp &resp, const QString &dir)
{
    QList<MyObject> res;
    //获取文件列表
    const std::vector<Content>& contents = resp.GetContents();
    for(std::vector<Content>::const_iterator itr = contents.begin(); itr != contents.end(); ++itr)
    {
        const Content& content = *itr;
        QString key(content.m_key.c_str());
//        qDebug() << "file: " << key;
        QString name = key.mid(dir.size());
        if(key != dir) //排除掉父目录本身，它一般隐藏不显示
        {
            MyObject object;
            object.name = name;
            object.lastmodified = QString(content.m_last_modified.c_str());
            object.size = QString(content.m_size.c_str()).toULongLong();
            object.dir = dir;
            res.append(object);
//            qDebug() << "fileName: " << object.name;
        }
    }
    return res;
}

MyBucket DaoCloudsCos::getBucketByName(const QString &bucketName)
{
    QList<MyBucket> bs = buckets();

    for(const auto& b : qAsConst(bs)){
        if(b.name == bucketName){
            return b;
        }
    }
    return MyBucket();
}
