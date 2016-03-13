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
    QString expToStr(QMExp exp);
    QString groupsToStr(vector<QMExp> groups);
    Groups strToGroups(QString str);

private Q_SLOTS:

    void opsMatchTest_data();
    void opsMatchTest();

    void toGroupsTest_data();
    void toGroupsTest();

    void firstMatchTest_data();
    void firstMatchTest();

    void secMatchTest_data();
    void secMatchTest();

    void macthTest_data();
    void macthTest();

};

QString QMMtest::expToStr(QMExp exp)
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

QMExp QMMtest::strToExp(QString str)
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

QString QMMtest::groupsToStr(vector<QMExp> groups)
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

Groups QMMtest::strToGroups(QString str)
{
    Groups res;
    QMExp curr_group;
    QMOperand curr_op;
    for(int i=0; i<str.size(); i++)
    {
        if(str[i]==';')
        {
            res.push_back(curr_group);
            curr_group.clear();
        }else if(str[i]==' ')
        {
            curr_group.push_back(curr_op);
            curr_op.vars.clear();
        }else
        {
            curr_op.vars.push_back(str[i]);
        }
    }
    return res;
}




void QMMtest::opsMatchTest_data()
{
    QTest::addColumn<QString>("op1");
    QTest::addColumn<QString>("op2");
    QTest::addColumn<QString>("result");
    QTest::addColumn<int>("match_index");
    QTest::addColumn<int>("opsize");

    QTest::newRow("2T")<<"00"<<"10"<<"-0"<<0<<2;
    QTest::newRow("2F")<<"10"<<"01"<<""<<-1<<2;
    QTest::newRow("3T")<<"101"<<"111"<<"1-1"<<1<<3;
    QTest::newRow("dif len, !=opsize")<<"10"<<"110"<<""<<-1<<3;
    QTest::newRow("same len, !=opsize")<<"10"<<"11"<<""<<-1<<3;
    QTest::newRow("2step T")<<"1-01"<<"1-00"<<"1-0-"<<3<<4;
    QTest::newRow("2step F same - pos")<<"1-01"<<"0-11"<<""<<-1<<4;
    QTest::newRow("2step F dif - pos")<<"1-01"<<"10-1"<<""<<-1<<4;
}

void QMMtest::opsMatchTest()
{
    QFETCH(QString, op1);
    QFETCH(QString, op2);
    QFETCH(int, opsize);
    QFETCH(QString, result);
    QFETCH(int, match_index);

    QMMinimizerT qmm;
    qmm.set_opsize(opsize);
    QString test_res;
    QMOperand operand1(op1);
    QMOperand operand2(op2);


    int tst_index;
    QMOperand *mres;
    std::tie(mres, tst_index) = qmm.matchOps(operand1, operand2);
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
    qmm.set_opsize(tstexp[0].vars.size());
    Groups test_res;
    qmm.toGroups(tstexp, test_res);
    QCOMPARE(groupsToStr(test_res), result);
}




void QMMtest::firstMatchTest_data()
{
    QTest::addColumn<QString>("start_groups");
    QTest::addColumn<QString>("result");
    QTest::addColumn<QString>("res_exp");
    QTest::addColumn<int>("opsize");

    QTest::newRow("0,1,2,3")<<"000 ;001 010 ;011 ;"<<";0-0 0-1 ;00- 01- ;"<<""<<3;
}

void QMMtest::firstMatchTest()
{
    QFETCH(QString, start_groups);
    QFETCH(QString, result);
    QFETCH(QString, res_exp);
    QFETCH(int, opsize);

    QMMinimizerT qmm;
    QMExp tstexp;
    qmm.set_opsize(opsize);
    Groups test_res = strToGroups(start_groups);
    qmm.firstMatch(tstexp, test_res);
    QCOMPARE(groupsToStr(test_res), result);
    QCOMPARE(expToStr(tstexp), res_exp);
}




void QMMtest::secMatchTest_data()
{
    QTest::addColumn<QString>("groups");
    QTest::addColumn<QString>("result");
    QTest::addColumn<QString>("start_exp");
    QTest::addColumn<QString>("res_exp");
    QTest::addColumn<int>("opsize");

    QTest::newRow("0,1,2,3")<<";0-0 0-1 ;00- 01- ;"<<";0-- ;0-- ;"<<""<<""<<3;
}

void QMMtest::secMatchTest()
{
    QFETCH(QString, groups);
    QFETCH(QString, result);
    QFETCH(QString, start_exp);
    QFETCH(QString, res_exp);
    QFETCH(int, opsize);

    QMMinimizerT qmm;
    qmm.set_opsize(opsize);
    Groups test_res = strToGroups(groups);
    QMExp test_exp = strToExp(start_exp);
    qmm.secMatch(test_exp, test_res);
    QCOMPARE(groupsToStr(test_res), result);
    QCOMPARE(expToStr(test_exp), res_exp);
}




void QMMtest::macthTest_data()
{
    QTest::addColumn<QString>("expression");
    QTest::addColumn<QString>("result");

    QTest::newRow("0,1,2,3")<<"000+001+010+011"<<"0--";
    QTest::newRow("0,1,3,5")<<"000+001+011+111"<<"-11 0-1 00-";
}

void QMMtest::macthTest()
{
    QFETCH(QString, expression);
    QFETCH(QString, result);

    QMMinimizerT qmm;
    QMExp test_exp = strToExp(expression);
    qmm.set_opsize(test_exp[0].vars.size());

    QCOMPARE(expToStr(qmm.match(test_exp)), result);
}


QTEST_APPLESS_MAIN(QMMtest)

#include "tst_qmm.moc"
