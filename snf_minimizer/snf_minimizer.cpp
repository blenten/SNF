#include "snf_minimizer.h"

///------------SNF-------------///
// for testing
void SNF_Minimizer::printOps()
{
    if(exp.empty())
    {
        cout<<"exp is empty!\n";
    }else
    {
        for(int i=0; i<(int)exp.size(); i++)
        {
            for(int j=0; j<(int)exp[i].size(); j++)
            {
                if(exp[i][j].invertion)
                {
                    cout<<'!'<<exp[i][j].name;
                }else
                {
                    cout<<exp[i][j].name;
                }
            }
            cout<<' ';
        }
    }
    cout<<"\nF_Type returned: "<<expType<<endl;
}
///CONSTRUCTOR
SNF_Minimizer::SNF_Minimizer()
{
    expType = NOTYPE;   // needed for testing. not nessesery
    exp.clear();
}
/// MINIMIZE
string SNF_Minimizer::minimize(string input)
{
    string output;
    cout<<"Parsing...";
    expType = parser.parse(input, exp);
    cout<<"DONE:\n";
    printOps();
    cout<<"\nMatching...";
    match();
    cout<<"DONE:\n";
    printOps();
    cout<<"\nNesschecking...";
    delNeedless();
    cout<<"DONE:\n";
    printOps();
    return output;
}

/// MATCH
void SNF_Minimizer::match()
{
    vector<Operand> temp;
    for(int i=0; i<(int)exp.size()-1; i++)
    {
        for(int j=i+1; j<(int)exp.size(); j++)
        {
            matchOperands(exp[i], exp[j], temp);
        }
    }
    exp.clear();
    exp = temp;
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
/// DEL UNNESSESARY
void SNF_Minimizer::delNeedless()
{
    int i=0;
    while(i<(int)exp.size())
    {
        if(!checkNecessity(i))  // if exp[i] needless
        {
            exp.erase(exp.begin()+i);   //erase exp[i]
        }else
        {
            i++;
        }
    }
}
/// NECESSITY CHECK
bool SNF_Minimizer::checkNecessity(int index)
{
    int res=0;    //resulting coef

    for(int i=0; i<(int)exp.size(); i++)
    {
        if(i!=index)
        {
            for(int j=0; j<(int)exp[i].size(); j++)
            {
                res += inop(exp[i][j], exp[index]);
            }
        }
    }

    if(res<=0)  return true;
    return false;
}
// INOP
INOP_t SNF_Minimizer::inop(Variable &var, Operand &op)
{
    for(int i=0; i<(int)op.size(); i++)
    {
        if(var.name==op[i].name)
        {
            if(var.invertion==op[i].invertion)  return IN;
            return invIN;
        }
    }
    return NIN;
}
