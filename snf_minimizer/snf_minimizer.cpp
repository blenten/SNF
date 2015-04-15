#include "snf_minimizer.h"

///------------VAR-------------///
Variable::Variable(string name, bool invertion=false)
{
    this->name = name;
    this->invertion = invertion;
}
bool Variable::operator==(Variable &var)
{
    if(name==var.name && invertion==var.invertion)  return true;
    return false;
}

///------------SNF-------------///

// TEST
void SNF_Minimizer::test()
{
    Variable x1("x1", false),x2("x2", false),x3("x3", false);
    expr.resize(3);
    expr[0].push_back(x1);
    expr[0].push_back(x2);
    expr[0].push_back(x3);
    x1.invertion = true;
    expr[1].push_back(x1);
    expr[1].push_back(x2);
    expr[1].push_back(x3);
    x2.invertion = true;
    expr[2].push_back(x1);
    expr[2].push_back(x2);
    expr[2].push_back(x3);

    printOps();
    match();
    printOps();
}
void SNF_Minimizer::printOps()
{
    for(int i=0; i<(int)expr.size(); i++)
    {
        for(int j=0; j<(int)expr[i].size(); j++)
        {
            if(expr[i][j].invertion)
            {
                cout<<'!'<<expr[i][j].name;
            }else
            {
                cout<<expr[i][j].name;
            }
        }
        cout<<' ';
    }
    cout<<endl;
}
/// MINIMIZE
string SNF_Minimizer::minimize(string input)
{
    string output;
    ///parser.parse(input, ops, expType);
    match();
    return output;
}

/// MATCH
void SNF_Minimizer::match()
{
    Expression temp;
    for(int i=0; i<(int)expr.size()-1; i++)
    {
        for(int j=i+1; j<(int)expr.size(); j++)
        {
            matchOperands(expr[i], expr[j], temp);
        }
    }
    expr.clear();
    expr = temp;
}
// subMatch
void SNF_Minimizer::matchOperands(Operand &op1, Operand &op2, Expression &result)
{
    Operand res_op;
    for(int i=0; i<(int)op1.size(); i++)
    {
        if(op1[i]==op2[i])  res_op.push_back(op1[i]);
    }

    if(res_op.size()==(op1.size()-1))   result.push_back(res_op);
}
/// NESSESERITY CHECK
void SNF_Minimizer::delunness()
{
    bool ext;
    for(int i=0; i<(int)expr.size(); i++)
    {
       if(isUnness(expr[i]))
       {
           expr.
       }
    }
}
