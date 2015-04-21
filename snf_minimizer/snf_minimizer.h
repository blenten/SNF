#ifndef SNF_MINIMIZER_H
#define SNF_MINIMIZER_H

#include"../snf_parser/snf_parser.h"

using namespace std;

enum INOP_t
{
    IN=1, invIN=-1, NIN=0
};

/// MINIMIZER
class SNF_Minimizer
{
public:
    SNF_Minimizer();
    void printOps(); // for testing

    string minimize(string input);

private:
    void match();
    void delNeedless();
    string res_toString();
    bool checkNecessity(int index);
    INOP_t inop(Variable&, Operand&);
    void matchOperands(Operand& op1, Operand& op2, Expression& result);

    SNF_Parser parser; //olerapx
    Expression exp;
    FunctionType expType;
};

#endif // SNF_MINIMIZER_H
