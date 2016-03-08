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
    QMExp strToExp(QString &str);
    QString expToStr(QMExp &exp);
    QString groupsToStr(vector<QMExp> &groups);

private Q_SLOTS:

    void opsMatchTest_data();
    void opsMatchTest();

    void toGroupsTest_data();
    void toGroupsTest();

    void firstMatchTest_data();
    void firstMatchTest();

    void secMatchTest_data();
    void secMatchTest();

//    void macthTest_data();
//    void macthTest();

};

QString QMMtest::expToStr(QMExp &exp)
{
    if(exp.empty()) return "";
    QString res;
    res.push_back(exp[0].vars);
    for(size_t i=1; i<exp.size(); i++)
    {
        res.push_back(' ');
        res.push_back(exp[i].vars);
    }
    return res;
}

QMExp QMMtest::strToExp(QString &str)
{
    QMExp res;
    res.clear();
    QMOperand tOp;
    for(int i=0; i<str.size(); i++)
    {
        if(str[i]!='+')
        {
            tOp.vars.push_back(str[i]);
        }else
        {
            res.push_back(tOp);
            tOp.vars.clear();
        }
    }
    res.push_back(tOp);
    return res;
}

QString QMMtest::groupsToStr(vector<QMExp> &groups)
{
    if(groups.empty()) return "empty";
    QString res;
    for(size_t i=0; i<groups.size(); i++)
    {
        for(size_t j=0; j<groups[i].size(); j++)
        {
            res.append(groups[i][j].vars);
            res.push_back(' ');
        }
        res.push_back(';');
    }
    return res;
}





void QMMtest::opsMatchTest_data()
{
    QTest::addColumn<QString>("op1");
    QTest::addColumn<QString>("op2");
    QTest::addColumn<QString>("result");
    QTest::addColumn<int>("match_index");

    QTest::newRow("2T")<<"00"<<"10"<<"-0"<<0;
    QTest::newRow("2F")<<"10"<<"01"<<""<<-1;
    QTest::newRow("3T")<<"101"<<"111"<<"1-1"<<1;
    QTest::newRow("dif len")<<"10"<<"110"<<""<<-1;
    QTest::newRow("2step T")<<"1-01"<<"1-00"<<"1-0-"<<3;
    QTest::newRow("2step F same - pos")<<"1-01"<<"0-11"<<""<<-1;
    QTest::newRow("2step F dif - pos")<<"1-01"<<"10-1"<<""<<-1;
}

void QMMtest::opsMatchTest()
{
    QFETCH(QString, op1);
    QFETCH(QString, op2);
    QFETCH(QString, result);
    QFETCH(int, match_index);

    QMMinimizerT qmm;
    QString test_res;
    QMOperand operand1(op1);
    QMOperand operand2(op2);


    int tst_index;
    QMOperand *mres = qmm.matchOps(operand1, operand2, tst_index);
    if(mres==nullptr)
    {
        test_res = "";
    }else
    {
        test_res = mres->vars;
    }
    delete mres;
    QCOMPARE(test_res, result);
    QCOMPARE(tst_index, match_index);
}





void QMMtest::toGroupsTest_data()
{
    QTest::addColumn<QString>("expression");
    QTest::addColumn<QString>("result");

    QTest::newRow("3v; 1 op in each g")<<"000+001+011+111"<<"000 ;001 ;011 ;111 ;";
    QTest::newRow("3v; all in 1 g")<<"001+010+100"<<";001 010 100 ;;;";
}

void QMMtest::toGroupsTest()
{
    QFETCH(QString, expression);
    QFETCH(QString, result);

    QMMinimizerT qmm;
    QMExp tstexp = strToExp(expression);
    Groups test_res;
    qmm.toGroups(tstexp, test_res);
    QCOMPARE(groupsToStr(test_res), result);
}




void QMMtest::firstMatchTest_data()
{
    QTest::addColumn<QString>("expression");
    QTest::addColumn<QString>("result");
    QTest::addColumn<QString>("res_exp");

    QTest::newRow("0,1,2,3")<<"000+001+010+011"<<";0-0 0-1 ;00- 01- ;"<<"";
}

void QMMtest::firstMatchTest()
{
    QFETCH(QString, expression);
    QFETCH(QString, result);
    QFETCH(QString, res_exp);

    QMMinimizerT qmm;
    QMExp tstexp = strToExp(expression);
    Groups test_res;
    qmm.firstMatch(tstexp, test_res);
    QCOMPARE(groupsToStr(test_res), result);
    QCOMPARE(expToStr(tstexp), res_exp);
}




void QMMtest::secMatchTest_data()
{
    QTest::addColumn<
}

//void QMMtest::macthTest_data()
//{
//    QTest::addColumn<QString>("expression");
//    QTest::addColumn<QString>("result");

//    QTest::newRow("0,1,3,5")<<"000+001+011+111"<<"00- 0-1 -11";
//}

//void QMMtest::macthTest()
//{
//    QFETCH(QString, expression);
//    QFETCH(QString, result);

//    QMMinimizerT qmm;
//    qmm.exp = strToExp(expression);
//    qmm.match();

//    QCOMPARE(expToStr(qmm.exp), result);
//}


QTEST_APPLESS_MAIN(QMMtest)

#include "tst_qmm.moc"
