#include <QtTest>

// add necessary includes here

#include "src/config/exceptions.h"

class TestExceptions : public QObject
{
    Q_OBJECT

public:
    TestExceptions();
    ~TestExceptions();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

TestExceptions::TestExceptions()
{

}

TestExceptions::~TestExceptions()
{

}

void TestExceptions::initTestCase()
{

}

void TestExceptions::cleanupTestCase()
{

}

void TestExceptions::test_case1()
{
    //TODO ../../cosbrowser/static/docs/errorcode.csv不正确？？？
    BaseException::generateErrorCodeHFile("../../../19-5/cosbrowser/static/docs/errorcode.csv",
                                          "../../../19-5/cosbrowser/src/config/errorcode.h");
//    qDebug() << BaseException(EC_211100).msg();
}

QTEST_APPLESS_MAIN(TestExceptions)

#include "tst_testexceptions.moc"
