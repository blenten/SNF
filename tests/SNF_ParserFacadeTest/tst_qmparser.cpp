#include <QString>
#include <QtTest>

#include "../../classes/snf_parser/snf_parserfacade.h"

class SNF_ParserFacadeT: public SNF_ParserFacade
{
    friend class QMParserTest;
};

class QMParserTest: public QObject
{
    Q_OBJECT

public:

private Q_SLOTS:
    void QMExpConvertTest_data();
    void  QMExpConvertTest();
};

void QMParserTest::QMExpConvertTest_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QVector<QString>>("result");

    QVector<QString> vec;
    vec = {"1101","0101"};
    QTest::newRow("SNKF normal test")<<"(x1+x2+!x3+x4)*(!x1+x2+!x3+x4)"<<vec;

    vec = {"1101","0101"};
    QTest::newRow("SNDF normal test")<<"(x1*x2*!x3*x4)+(!x1*x2*!x3*x4)"<<vec;

    vec = {"1"};
    QTest::newRow("SNF 1-op test")<<"x1"<<vec;
}

void QMParserTest::QMExpConvertTest()
{
    QFETCH(QString, input);
    QFETCH(QVector<QString>, result);

    SNF_ParserFacade parser;
    QMExp res;
    parser.parse(input.toStdString(), res);
    QVector<QString> output;

    for(size_t i=0;i<res.size();i++)
        output.push_back(res[i].vars);

    QCOMPARE(output,result);
}

QTEST_APPLESS_MAIN(QMParserTest)
#include "tst_qmparser.moc"
