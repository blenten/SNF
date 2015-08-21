#include "snf_minimizer.h"
//------------SNF-------------//

string SNF_Minimizer::getLog()
{
    return logs.str();
}

void SNF_Minimizer::log()
{
    if(exp.empty())
    {
        logs<<"%ExpressionIsEmpty"<<"\n";
    }else
    {
        int size = (int) exp.size();
        for(int i=0; i<size; i++)
        {
            for(int j=0; j<(int)exp[i].size(); j++)
            {
                if(exp[i][j].invertion)
                {
                    logs<<'!'<<exp[i][j].name;
                }else
                {
                    logs<<exp[i][j].name;
                }
            }
            logs<<'\t';
        }
    }
    logs<<endl;
}
//CONSTRUCTOR
SNF_Minimizer::SNF_Minimizer()
{
    exp.clear();
}
//PARSE
bool SNF_Minimizer::parse(string input)
{
    try
    {
        expType = parser.parse(input, exp);
    }catch(InvalidFunctionException e)
    {
         logs<<e.getError()<<"\n";
        return true;
    }
    if(exp.size()<=1)
    {
        logs<<"%Default"<<"\n";
        return true;
    }
    log();
    return false;
}

// OUTPUT
string SNF_Minimizer::res_toString()
{
    string output;
    int size = (int)exp.size();
    for(int i=0; i<size; i++)
    {
        if(expType==SNKF) output += '(';
        for(int j=0; j<(int)exp[i].size(); j++)
        {
            if(exp[i][j].invertion==true) output += '!';
            output += exp[i][j].name;
            if(expType==SNKF && (exp[i].size()-j)>1) output += '+';
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
        for(int j=i+1; j<size; j++)
        {
            matchOperands(exp[i], exp[j], temp);
        }
    }

    if(!temp.empty())
    {
        exp.clear();
        exp = temp;
    }
    //
    log();
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

    if(exp.size()<=1)
    {
        return;
    }

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
    //
    log();
}
// NECESSITY CHECK
bool SNF_Minimizer::checkNecessity(int index)
{
    int res=0;
    Expression NINs;
    for(int i=0; i<(int)exp.size(); i++)
    {
        if(i!=index)
        {
            int tempres=1;
            Operand op;
            for(int j=0; j<(int)exp[i].size(); j++)
            {
                INOP_t temp = inop(exp[i][j], exp[index]);
                if(temp==invIN)
                {
                    tempres = 0;
                    op.clear();
                    break;
                }else if(temp==NIN)
                {
                    tempres = 0;
                    op.push_back(exp[i][j]);
                }
            }
            if(!op.empty())
            {
                NINs.push_back(op);
            }
            res += tempres;
        }
    }

    if(res==0)
    {
        if(NINs.empty())
        {
            return true;
        }else
        {
            for(int i=0; i<(int)NINs.size()-1; i++)
            {
                for(int j=i+1; j<(int)NINs.size(); j++)
                {
                    if(NINs[i].size()==1 && NINs[j].size()==1 && NINs[i][0].name==NINs[j][0].name && NINs[i][0].invertion!=NINs[j][0].invertion)
                    {
                        return false;
                    }
                }
            }
            return true;
        }
    }
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
