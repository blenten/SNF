#ifndef SNF_MINIMIZER_H
#define SNF_MINIMIZER_H

#include<iostream>
#include<string>
#include<vector>

using namespace std;

// temporary
enum FunctionType
{
    SNDF,
    SNKF
};

/// VAR & OPERAND
class Variable
{
public:
    Variable(string, bool);
    bool operator==(Variable&);
    string name;
    bool invertion;
};
typedef vector<Variable> Operand;
typedef vector<Operand> Expression;


/// MINIMIZER

class SNF_Minimizer
{
public:
    void test(); // while parser isn't ready
    void printOps(); // for testing

    string minimize(string);
    void match();
    void delunness(); // izbitochnost
private:
    void matchOperands(Operand&, Operand&, Expression&);
    ///ExpParser parser; //olerapx
    Expression expr;
    int expType;
};

#endif // SNF_MINIMIZER_H
