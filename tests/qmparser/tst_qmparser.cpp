#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include "snf_parser/snf_parserfacade.h"

class SNF_ParserFacadeT: public SNF_ParserFacade
{
    friend class QMParserTest;
};

class QMParserTest: public QObject
{
    Q_OBJECT

public:

private slots:
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
    std::pair<Expression, FunctionType> res = parser.parse(input.toStdString());
    QVector<QString> output;

//    for(size_t i=0;i<res.first.size();i++)
//        output.push_back(res.first[i].variables);

//    QCOMPARE(output,result);
    /// TODO: broken, wont compile
}

QTEST_MAIN(QMParserTest)

#include "tst_qmparser.moc"
