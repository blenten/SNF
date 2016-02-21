#include <QString>
#include <QtTest>

#include "../../classes/qmm/qm_minimizer.h"


class QMMinimizerT : public QM_Minimizer
{
    friend class QMMtest;
};

class QMMtest : public QObject
{
    Q_OBJECT
public:
//    QMMtest();
    QMExp strToExp(QString str);

private Q_SLOTS:

    void opsMatchTest_data();
    void opsMatchTest();
};

QMExp QMMtest::strToExp(QString str)
{
    QMExp res;
    res.clear();
    QString ops;
    ops.clear();
    for(int i=0; i<(int)str.size(); i++)
    {
        if(str[i]!='+')
        {
            ops.push_back(str[i]);
        }else
        {
            res.push_back(*(new QMOperand(ops)));
            ops.clear();
        }
    }
    return res;
}

void QMMtest::opsMatchTest_data()
{
    QTest::addColumn<QString>("op1");
    QTest::addColumn<QString>("op2");
    QTest::addColumn<QString>("result");

    QTest::newRow("2T")<<"00"<<"10"<<"-0";
    QTest::newRow("2F")<<"10"<<"01"<<"";
    QTest::newRow("3T")<<"101"<<"111"<<"1-1";
    QTest::newRow("dif len")<<"10"<<"110"<<"";
    QTest::newRow("2step T")<<"1-01"<<"1-00"<<"1-0-";
    QTest::newRow("2step F same - pos")<<"1-01"<<"0-11"<<"";
    QTest::newRow("2step F dif - pos")<<"1-01"<<"10-1"<<"";
}

void QMMtest::opsMatchTest()
{
    QFETCH(QString, op1);
    QFETCH(QString, op2);
    QFETCH(QString, result);

    QMMinimizerT qmm;
    QString test_res;
    QMOperand *mres = qmm.matchOps(*(new QMOperand(op1)), *(new QMOperand(op2)));
    if(mres==nullptr)
    {
        test_res = "";
    }else
    {
        test_res = mres->vars;
    }
    QCOMPARE(test_res, result);
}



QTEST_APPLESS_MAIN(QMMtest)

#include "tst_qmm.moc"
