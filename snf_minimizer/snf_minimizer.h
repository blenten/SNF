#ifndef SNF_MINIMIZER_H
#define SNF_MINIMIZER_H

#include"../snf_parser/snf_parser.h"

using namespace std;

/// MINIMIZER

class SNF_Minimizer
{
public:
    SNF_Minimizer();
    void printOps(); // for testing

    string minimize(string);
    void match();
    void delUnness(); // izbitochnost
private:
    void matchOperands(Operand&, Operand&, Expression&);
    SNF_Parser parser; //olerapx
    Expression exp;
    FunctionType expType;
};

#endif // SNF_MINIMIZER_H
