#ifndef SNF_MINIMIZER_H
#define SNF_MINIMIZER_H

#include "snf_parser/snf_parserfacade.h"
#include <sstream>
#include <QObject>

using namespace std;

enum INOP_type
{
    IN=1, invIN=0, NIN=-1
};

class SNF_Minimizer: public QObject
{
    Q_OBJECT

public:
    SNF_Minimizer();

    QString minimize (QString input);

    bool parse(string input);

    void match();

    void delUnness();

    string res_toString();

private:
    bool checkNecessity(int index);

    void sortres(int left, int right, Expression& res);

    INOP_type inop(Variable&, Operand&);

    bool resolves(Expression& exp);

    bool matchOperands(Operand& op1, Operand& op2, Expression& result);

    bool containsAllOperands();

    void delsame(Expression& expression);

    QString expToQStr(Expression&);         //creating log for "steps"

    void logResult();

    SNF_ParserFacade parser; ///<olerapx
    Expression exp; ///<
    FunctionType expType; ///<

signals:
    void sendCondition(QString condition);
    void sendLog(QString log);
    void sendSleep (int ms);
    void sendProgress (int val);
};

#endif // SNF_MINIMIZER_H
