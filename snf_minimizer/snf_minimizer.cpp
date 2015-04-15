#include "snf_minimizer.h"

///------------VAR-------------///
Variable::Variable(string name, bool invertion=false)
{
    this->name = name;
    this->invertion = invertion;
}
bool Variable::operator==(Variable var)
{
    if(name==var.name && invertion==var.invertion)  return true;
    return false;
}

///------------SNF-------------///

// TEST
void SNF_Minimizer::test()
{
    Variable x1("x1", false),x2("x2", false),x3("x3", false);
    ops.resize(3);
    ops[0].push_back(x1);
    ops[0].push_back(x2);
    ops[0].push_back(x3);
    x1.invertion = true;
    ops[1].push_back(x1);
    ops[1].push_back(x2);
    ops[1].push_back(x3);
    x2.invertion = true;
    ops[2].push_back(x1);
    ops[2].push_back(x2);
    ops[2].push_back(x3);

    printOps();
    match();
    printOps();
}
void SNF_Minimizer::printOps()
{
    for(int i=0; i<(int)ops.size(); i++)
    {
        for(int j=0; j<(int)ops[i].size(); j++)
        {
            if(ops[i][j].invertion)
            {
                cout<<'!'<<ops[i][j].name;
            }else
            {
                cout<<ops[i][j].name;
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
    vector<Operand> temp;
    for(int i=0; i<(int)ops.size()-1; i++)
    {
        for(int j=i+1; j<(int)ops.size(); j++)
        {
            matchOperands(ops[i], ops[j], temp);
        }
    }
    ops.clear();
    ops = temp;
}
// subMatch
void SNF_Minimizer::matchOperands(Operand &op1, Operand &op2, vector<Operand> &result)
{
    Operand res_op;
    for(int i=0; i<(int)op1.size(); i++)
    {
        if(op1[i]==op2[i])  res_op.push_back(op1[i]);
    }

    if(res_op.size()==(op1.size()-1))   result.push_back(res_op);
}
/// EXTCHECK
void SNF_Minimizer::extCheck()
{
    bool ext;
    for(int i=0; i<(int)ops.size(); i++)
    {
        if(expType==SNDF)
        {
            ext = D_check(ops[i]);
        }else if(expType==SNCF)
        {
            ext = C_check(ops[i]);
        }else
        {
            cout<<"wrong type\n";
        }
    }
}
