#include <QString>
#include <QtTest>

#include "../../classes/qmm/qm_minimizer.h"

class FakeParser : public SNF_ParserFacade
{
public:
    FakeParser(QMExp &expr, FunctionType &ftype);
    QMExp expr;
    FunctionType ftype;
    pair<QMExp, FunctionType> parse(QString input);
};
FakeParser::FakeParser(QMExp &expr, FunctionType &ftype)
{
    this->expr = expr;
    this->ftype = ftype;
}
pair<QMExp, FunctionType> FakeParser::parse(QString input)
{
    pair<QMExp, FunctionType> res;
    res.first = expr;
    res.second = ftype;
    return res;
}



class QMMinimizerT : public QM_Minimizer
{
    friend class QMMtest;
public:
    QMExp exp;
    FunctionType type;
    SNF_ParserFacade* createParser();
};

SNF_ParserFacade* QMMinimizerT::createParser()
{
    return new FakeParser(exp, type);
}


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

    void cutCoreTest_data();
    void cutCoreTest();

    void getOptimalCoverTest_data();
    void getOptimalCoverTest();

    void minimizeTest_data();
    void minimizeTest();

};

QString QMMtest::expToStr(QMExp exp)
{
    if(exp.empty()) return "";
    QString res;
    res.clear();
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
    if(str=="")
    {
        return res;
    }
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
    QTest::newRow("0v") << "" << "empty";
    QTest::newRow("5v; len 5 with repeats") << "00010+00010+11001+11000+00101" << ";00010 00010 ;11000 00101 ;11001 ;;;";
    QTest::newRow("2v; 1 op") << "01" << ";01 ;;";
}

void QMMtest::toGroupsTest()
{
    QFETCH(QString, expression);
    QFETCH(QString, result);

    QMMinimizerT qmm;
    QMExp test_exp = strToExp(expression);
    if(test_exp.empty())
    {
        qmm.set_opsize(0);
    }else
    {
        qmm.set_opsize(test_exp[0].vars.size());
    }
    Groups test_res;
    qmm.toGroups(test_exp, test_res);
    QCOMPARE(groupsToStr(test_res), result);
}




void QMMtest::firstMatchTest_data()
{
    QTest::addColumn<QString>("start_groups");
    QTest::addColumn<QString>("result");
    QTest::addColumn<QString>("res_exp");
    QTest::addColumn<int>("opsize");

    QTest::newRow("0,1,2,3")<<"000 ;001 010 ;011 ;"<<";0-0 0-1 ;00- 01- ;"<<""<<3;
    QTest::newRow("3 g, first empty") << ";001 010 ; 011 ;" << ";0-1 ;01- ;"<<""<<3;
    QTest::newRow("1 g") << "0 ;" << "empty" << "0" << 1;
    QTest::newRow ("empty") << ";" << "empty" << "" << 0;
    QTest::newRow("one alone") << "000 ;001 ;111 ;" << ";;00- ;" << "111" << 3;
}

void QMMtest::firstMatchTest()
{
    QFETCH(QString, start_groups);
    QFETCH(QString, result);
    QFETCH(QString, res_exp);
    QFETCH(int, opsize);

    QMMinimizerT qmm;
    QMExp test_exp;
    qmm.set_opsize(opsize);
    Groups test_res = strToGroups(start_groups);
    qmm.firstMatch(test_exp, test_res);
    QCOMPARE(groupsToStr(test_res), result);
    QCOMPARE(expToStr(test_exp), res_exp);
}




void QMMtest::secMatchTest_data()
{
    QTest::addColumn<QString>("groups");
    QTest::addColumn<QString>("result");
    QTest::addColumn<QString>("start_exp");
    QTest::addColumn<QString>("res_exp");
    QTest::addColumn<int>("opsize");

    QTest::newRow("0,1,2,3")<<";0-0 0-1 ;00- 01- ;"<<";0-- ;0-- ;"<<""<<""<<3;
    QTest::newRow("empty") << " ;" << "empty" << "" <<"" << 0;
    QTest::newRow("one alone") << "00- 01- ;0-0 ;" << ";0-- ;;" << "000" << "000 0-0"<<3;
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
    QTest::newRow("empty") << ""<<"";
    QTest::newRow("1 op") << "000" << "000";
    QTest::newRow("1 not matched") << "001+110+011" << "110 0-1";
}

void QMMtest::macthTest()
{
    QFETCH(QString, expression);
    QFETCH(QString, result);

    QMMinimizerT qmm;
    QMExp test_exp = strToExp(expression);
    if(test_exp.empty())
    {
        qmm.set_opsize(0);
    }else
    {
        qmm.set_opsize(test_exp[0].vars.size());
    }

    QCOMPARE(expToStr(qmm.match(test_exp)), result);
}


void QMMtest::cutCoreTest_data()
{
    QTest::addColumn<QString>("input_ops");
    QTest::addColumn<QString>("matched_ops");
    QTest::addColumn<QString>("result");
    QTest::addColumn<QString>("res_input_exp");
    QTest::addColumn<QString>("res_matched_exp");

    QTest::newRow("all core")<<"001+000+101+111"<<"0-0+11-+-01"<<"-01 0-0 11-"<< ""<< "";
    QTest::newRow("t1")<<"000+010+101+110+111"<<"1-1+0-0+-10+11-"<<"0-0 1-1"<<"110"<<"-10 11-";
}

void QMMtest::cutCoreTest()
{
    QFETCH(QString, input_ops);
    QFETCH(QString, matched_ops);
    QFETCH(QString, result);
    QFETCH(QString, res_input_exp);
    QFETCH(QString, res_matched_exp);

    QMMinimizerT qmm;
    QMExp test_input = strToExp(input_ops);
    QMExp test_matched_ops = strToExp(matched_ops);
    QMExp test_exp = qmm.cutCore(test_matched_ops, test_input);

    QCOMPARE(expToStr(test_exp), result);
    QCOMPARE(expToStr(test_input), res_input_exp);
    QCOMPARE(expToStr(test_matched_ops), res_matched_exp);

}


void QMMtest::getOptimalCoverTest_data()
{
    QTest::addColumn<QString>("input_ops");
    QTest::addColumn<QString>("matched_ops");
    QTest::addColumn<QString>("result");

    QTest::newRow("simple rating test")<<"001+101+110+111"<<"-0-+-01+11-+1--"<<"1-- -0-";
    QTest::newRow("needless skipping test")<<"001+101+110+111"<<"-01+-0-+11-"<<"-0- 11-";
}

void QMMtest::getOptimalCoverTest()
{
    QFETCH(QString, input_ops);
    QFETCH(QString, matched_ops);
    QFETCH(QString, result);

    QMMinimizerT qmm;
    QMExp test_input = strToExp(input_ops);
    QMExp test_matched_ops = strToExp(matched_ops);
    QMExp test_result;
    test_result = qmm.getOptimalCover(test_matched_ops, test_input);

    QCOMPARE(expToStr(test_result), result);
}


void QMMtest::minimizeTest_data()
{
    QTest::addColumn<QString>("expression");
    QTest::addColumn<int>("ftype");
    QTest::addColumn<QString>("result");

    QTest::newRow("0,1,2,5 SDNF")<<"000+001+010+101"<<static_cast<int>(SNDF)<<"!x1!x3+!x2x3+!x1!x2";
    QTest::newRow ("0,2,5,6,7 SDNF") << "000+010+101+110+111" << static_cast<int>(SNDF)<<"!x1!x3+x1x3+x2!x3";
}

void QMMtest::minimizeTest()
{
   QFETCH(QString, expression);
   QFETCH(int, ftype);
   QFETCH(QString, result);

   QMMinimizerT qmm;
   qmm.exp = strToExp(expression);
   qmm.type = static_cast<FunctionType>(ftype);
   QString test_res = qmm.minimize("piska");

   QCOMPARE(test_res, result);
}

QTEST_APPLESS_MAIN(QMMtest)

#include "tst_qmm.moc"
