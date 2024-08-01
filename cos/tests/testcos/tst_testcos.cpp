#include <QtTest>

// add necessary includes here
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

private:
    DaoCloudsCos m_cos;

};

TestCos::TestCos()
{

}

TestCos::~TestCos()
{

}

void TestCos::initTestCase()
{
    m_cos.login("AKIDHgyY7e7bRE7sW2qrkU97QgyhceCiBzYx","");
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

QTEST_APPLESS_MAIN(TestCos)

#include "tst_testcos.moc"
