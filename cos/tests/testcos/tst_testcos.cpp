#include "tst_testcos.h"

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
