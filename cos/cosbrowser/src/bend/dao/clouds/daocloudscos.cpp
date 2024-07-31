#include "daocloudscos.h"

#include "src/config/exceptions.h"
#include "src/config/errorcode.h"

#include "cos_api.h"
using namespace qcloud_cos;

// 指定配置文件路径，初始化CosConfig
static CosConfig config = CosConfig("./cosconfig.json");

DaoCloudsCos::DaoCloudsCos()
{
}

QList<MyBucket> DaoCloudsCos::buckets()
{
    QList<MyBucket> res;
    CosAPI cos = CosAPI(config);

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
        QString msg = QString::fromLocal8Bit("腾讯云错误码 【%1】：%2")
                .arg(result.GetErrorCode().c_str(), result.GetErrorMsg().c_str());
        throw BaseException(EC_211000, msg);
    }
    return res;
}

QList<MyBucket> DaoCloudsCos::login(const QString &secretId, const QString &secretKey)
{
    config.SetAccessKey(secretId.toStdString());
    config.SetSecretKey(secretKey.toStdString());
    config.SetRegion("ap-guangzhou"); //没这个会报错
    return buckets();
}
