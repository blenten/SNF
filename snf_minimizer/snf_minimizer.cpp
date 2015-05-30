#include "snf_minimizer.h"

//------------SNF-------------//
/// for testing
void SNF_Minimizer::printOps()
{
    if(exp.empty())
    {
        cout<<"exp is empty!\n";
    }else
    {
        int size = (int) exp.size();
        for(int i=0; i<size; i++)
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
            cout<<'\t';
        }
    }
    cout<<"\nF_Type returned: "<<expType<<endl;
}
//CONSTRUCTOR
SNF_Minimizer::SNF_Minimizer()
{
    exp.clear();
}
// MINIMIZE
string SNF_Minimizer::minimize(string input)
{
//    cout<<"Parsing...";
    try
    {
        expType = parser.parse(input, exp);
    }catch(InvalidFunctionException e)
    {
        cout<<"Nope.\n";
        return e.getError();
    }
//    cout<<"DONE:\n";
    if(exp.size()<=1)   return res_toString();
    printOps();
    cout<<"\nMatching...";
    match();
    cout<<"DONE:\n";
    printOps();
    cout<<"\nNesschecking...";
    delNeedless();
    cout<<"DONE:\n";
    printOps();
    cout<<"\n\n";
    return res_toString();
}

// OUTPUT
string SNF_Minimizer::res_toString()
{
    string output;
    int size = (int)exp.size();
    for(int i=0; i<(int)size; i++)
    {
        if(expType==SNKF) output += '(';
        for(int j=0; j<size; j++)
        {
            if(exp[i][j].invertion==true) output += '!';
            output += exp[i][j].name;
            if(expType==SNKF && (size-j)>1) output += '+';
        }
        if(expType==SNKF)output += ')';
        if(expType==SNDF && (size-i)>1) output += '+';
    }
    return output;
}

// MATCH
void SNF_Minimizer::match()
{
    int size = (int)exp.size();
    vector<Operand> temp;
    for(int i=0; i<size-1; i++)
    {
        bool merged = false;
        for(int j=i+1; j<size; j++)
        {
            merged = matchOperands(exp[i], exp[j], temp);
        }
        if(!merged)
        {
            temp.push_back(exp[i]);
        }
    }
    if(!temp.empty())
    {
        exp.clear();
        exp = temp;
    }
}
/// subMatch
bool SNF_Minimizer::matchOperands(Operand &op1, Operand &op2, Expression &result)
{
    Operand res_op;
    for(int i=0; i<(int)op1.size(); i++)
    {
        if(op1[i]==op2[i])  res_op.push_back(op1[i]);
    }

    if(res_op.size()==(op1.size()-1))
    {
        result.push_back(res_op);
        return true;
    }
    return false;
}
// DEL UNNESSESARY
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
// NECESSITY CHECK
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
