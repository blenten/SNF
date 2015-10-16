#ifndef SNF_MINIMIZER_H
#define SNF_MINIMIZER_H

#include "classes/snf_parser/snf_parserdecorator.h"
#include <sstream>

using namespace std;

enum INOP_t
{
    IN=1, invIN=0, NIN=-1
};

/// MINIMIZER
class SNF_Minimizer
{
public:
    SNF_Minimizer();

    bool parse(string input);
    void match();
    void delNeedless();
    string res_toString();
    string getLog();

    string minimize(string); //for tester only. needs fixing!

private:
    bool checkNecessity(int index);
    INOP_t inop(Variable&, Operand&);
    bool matchOperands(Operand& op1, Operand& op2, Expression& result);

    void log();         //creating log for "steps"
    stringstream logs;

    SNF_ParserDecorator parser; //olerapx
    Expression exp;
    FunctionType expType;
};

#endif // SNF_MINIMIZER_H
