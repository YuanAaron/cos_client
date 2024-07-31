#include <QtTest>

// add necessary includes here
#include "src/helper/filehelper.h"

class TestFileHelper : public QObject
{
    Q_OBJECT

public:
    TestFileHelper();
    ~TestFileHelper();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_readAllTxt();
    void test_joinPath();

};

TestFileHelper::TestFileHelper()
{

}

TestFileHelper::~TestFileHelper()
{

}

void TestFileHelper::initTestCase()
{

}

void TestFileHelper::cleanupTestCase()
{

}

void TestFileHelper::test_readAllTxt()
{
    QCOMPARE(FileHelper::readAllTxt(":/testfile.txt"),"abc");
}

void TestFileHelper::test_joinPath()
{
    QCOMPARE(FileHelper::joinPath("C:\\a\\b","c"),"C:/a/b/c");
}

QTEST_APPLESS_MAIN(TestFileHelper)

#include "tst_testfilehelper.moc"
