#ifndef SNF_MINIMIZER_H
#define SNF_MINIMIZER_H

#include<iostream>
#include<string>
#include<vector>

using namespace std;

// temporary
enum
{
    SNDF;
    SNCF;
};

/// VAR & OPERAND
class Variable
{
public:
    Variable(string, bool);
    bool operator==(Variable);
    string name;
    bool invertion;
};
typedef vector<Variable> Operand;


/// MINIMIZER

class SNF_Minimizer
{
public:
    void test(); // while parser isn't ready
    void printOps(); // for testing

    string minimize(string);
    void match();
    void extCheck(); // izbitochnost
private:
    void D_check(Operand&);
    void C_check(Operand&);
    void matchOperands(Operand&, Operand&, vector<Operand>&);
    ///ExpParser parser; //olerapx
    vector<Operand> ops;
    int expType;
};

#endif // SNF_MINIMIZER_H
