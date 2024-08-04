#ifndef TESTCOS_H
#define TESTCOS_H

#include <QtTest>

#include <src/bend/dao/clouds/daocloudscos.h>

class TestCos : public QObject
{
    Q_OBJECT

public:
    TestCos();
    ~TestCos();

private slots:
    //调用所有测试用例之前，先调用一次该函数
    void initTestCase();
    //调用所有测试用例之后，调用一次该函数
    void cleanupTestCase();
    void test_buckets();
    void test_isBucketExists();
    void test_getBucketLocation();
    void test_putBucket();
    void test_deleteBucket();
    void test_getObjects();

    void test_getObjects1_data();
    void test_getObjects1();

    void test_getObjectError();

    void test_putObject();
    void test_getObject();

private:
    DaoCloudsCos m_cos;
    QString m_secretId = "AKIDHgyY7e7bRE7sW2qrkU97QgyhceCiBzYx";
    QString m_secretKey = "LxeaPIXkt2P3hIiXN9Rix8DVsLvXAdBf";
    QString m_bucketName = "file-1303438180";

    QString m_uploadLocalPath = "./upload.txt";
    QString m_downloadLocalPath = "./download.txt";
    QString m_updownKey = "petclinic/jdbc/newUpload.txt";

};

#endif //TESTCOS_H
