#include "tst_testcos.h"

#include <src/config/exceptions.h>

TestCos::TestCos()
{

}

TestCos::~TestCos()
{

}

void TestCos::initTestCase()
{
    m_cos.login("AKIDHgyY7e7bRE7sW2qrkU97QgyhceCiBzYx","LxeaPIXkt2P3hIiXN9Rix8DVsLvXAdBf");
}

void TestCos::cleanupTestCase()
{

}

void TestCos::test_buckets()
{
    QList<MyBucket> buckets = m_cos.buckets();
    QVERIFY(buckets.size()>0); //QVERIFY进行bool表达式的判断
    QCOMPARE(buckets.size(),2); //QCOMPARE进行相等比较
}

void TestCos::test_isBucketExists()
{
    QVERIFY(m_cos.isBucketExists("file-1303438180"));
}

void TestCos::test_getBucketLocation()
{
    //因为登录时设置了Region为ap-guangzhou，这里只能测试Region为ap-guangzhou，否则报错
    QCOMPARE(m_cos.getBucketLocation("file-1303438180"),"ap-guangzhou");
}

void TestCos::test_putBucket()
{
    //添加后就不会执行该方法，也就不会干扰deleteBucket的测试
    QSKIP("SKIP test_putBucket");

    //创建存储桶时必须以-appid结尾
    m_cos.putBucket("cos-1303438180","ap-guangzhou");
    QVERIFY(m_cos.isBucketExists("cos-1303438180"));
}

void TestCos::test_deleteBucket()
{
    QSKIP("SKIP test_deleteBucket");

    //创建存储桶时必须以-appid结尾
    m_cos.deleteBucket("cos-1303438180");
    QVERIFY(!m_cos.isBucketExists("cos-1303438180"));
}

void TestCos::test_getObjects()
{
    QSKIP("SKIP test_getObjects");

    QList<MyObject> objList = m_cos.getObjects(m_bucketName, "");
    QCOMPARE(objList.size(), 7);
    objList = m_cos.getObjects(m_bucketName, "petclinic/");
    QCOMPARE(objList.size(), 13);
    objList = m_cos.getObjects(m_bucketName, "petclinic/jdbc/");
    QCOMPARE(objList.size(), 4);
}

void TestCos::test_getObjects1_data()
{
    //数据驱动第一阶段：准备测试数据（函数名称要以_data结尾
    QTest::addColumn<QString>("dir");
    QTest::addColumn<int>("expected");

    QTest::newRow("root") << "" << 7;
    QTest::newRow("subdir") << "petclinic/" << 13;
    QTest::newRow("leaf") << "petclinic/jdbc/" << 4;

}

void TestCos::test_getObjects1()
{
    //数据驱动第二阶段：从数据表读取数据，并执行比较
    QFETCH(QString, dir);
    QFETCH(int, expected);

    QList<MyObject> objList = m_cos.getObjects(m_bucketName, dir);
    QCOMPARE(objList.size(), expected);
}

void TestCos::test_getObjectError()
{
    //QVERIFY_EXCEPTION_THROWN 捕获预期异常
    QVERIFY_EXCEPTION_THROWN(m_cos.getObjects("file", ""), BaseException);
}

