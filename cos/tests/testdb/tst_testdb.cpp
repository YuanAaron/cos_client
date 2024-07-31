#include <QtTest>

// add necessary includes here

class TestDB : public QObject
{
    Q_OBJECT

public:
    TestDB();
    ~TestDB();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

TestDB::TestDB()
{

}

TestDB::~TestDB()
{

}

void TestDB::initTestCase()
{

}

void TestDB::cleanupTestCase()
{

}

void TestDB::test_case1()
{

}

QTEST_APPLESS_MAIN(TestDB)

#include "tst_testdb.moc"
