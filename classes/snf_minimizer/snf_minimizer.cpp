#include "snf_minimizer.h"
//------------SNF-------------//

string SNF_Minimizer::getLog()
{
    return logs.str();
}

void SNF_Minimizer::log(Expression &logex)
{
    if(logex.empty())
    {
        logs<<"%ExpressionIsEmpty\n";
    }else
    {
        int size = (int) logex.size();
        for(int i=0; i<size; i++)
        {
            for(int j=0; j<(int)logex[i].variables.size(); j++)
            {
                if(logex[i].variables[j].inversion)
                    logs<<'!';

                logs<<logex[i].variables[j].name;
                if (j < (int)logex[i].variables.size()-1) logs << (expType==SNKF? "+" :"*");
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
    if(exp.size()<1)
    {
        logs<<"%Default\n";
        return true;
    }
    logs<<"%Parsing\n";
    log(exp);
    if (containsAllOperands())
    {
        logs<<"\n";
        logs <<"%Result\n";
        logs<<"1";
        exp.clear();
        Operand op;
        op.variables.push_back(Variable("1", false));
        exp.push_back(op);
    }
    return false;
}
//ALL OPS
bool SNF_Minimizer::containsAllOperands()
{
    delsame(exp);
    uint64_t max = pow (2, exp.at(0).variables.size());
    uint64_t contains = exp.size();
    if (max==contains) return true;
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
        for(int j=0; j<(int)exp[i].variables.size(); j++)
        {
            if(exp[i].variables[j].inversion==true) output += '!';
            output += exp[i].variables[j].name;
            if(expType==SNKF && (exp[i].variables.size()-j)>1) output += '+';
        }
        if(expType==SNKF)output += ')';
        if(expType==SNDF && (size-i)>1) output += '+';
    }
    return output;
}
//DELSAME
void SNF_Minimizer::delsame(Expression &expression)
{
    if (expression.size()<=1) return;

    for(size_t i=0; i<expression.size()-1; i++)
    {
        size_t j=i+1;
        while(j<expression.size())
        {
            if(expression.at(i)==expression.at(j))
            {
                expression.erase(expression.begin()+j);
            }else
            {
                j++;
            }
        }
    }
}

// MATCH
void SNF_Minimizer::match()
{
    unsigned int iter = 1;
    vector<Operand> temp;
    vector<bool> matched;

    do{
        temp.clear();
        matched.resize(exp.size());
        for(int i=0; i<(int)matched.size(); i++) matched[i]=false;

        delsame(exp);
        if(exp[0].variables.size()>1) //la one-var-ops match costille
        {
            for(int i=0; i<(int)exp.size()-1; i++)
            {
                for(int j=i+1; j<(int)exp.size(); j++)
                {
                    if(matchOperands(exp[i], exp[j], temp)) //marks matched ops
                    {
                        matched[i]=true;
                        matched[j]=true;
                    }
                }
            }
        }
        if(!temp.empty())
        {
            for(int i=0; i<(int)exp.size(); i++)
            {
                if(!matched[i])     //adds ops that haven't matched to result
                {
                    temp.push_back(exp[i]);
                }
            }
            exp.clear();
            exp = temp;

            logs<<"\n";
            logs<<"%Matching@"<<iter<<":\n";
            log(exp);
            iter++;
        }
    }while(!temp.empty());
    delsame(exp);
}

/// subMatch
bool SNF_Minimizer::matchOperands(Operand &op1, Operand &op2, Expression &result)
{
    Operand res_op;
    for(int i=0; i<(int)op1.variables.size(); i++)
    {
        if(op1.variables[i].name!=op2.variables[i].name) return false;
        if(op1.variables[i]==op2.variables[i])  res_op.variables.push_back(op1.variables[i]);
    }

    if(res_op.variables.size()==(op1.variables.size()-1))
    {
        result.push_back(res_op);
        return true;
    }
    return false;
}

// DEL UNNESSESARY
void SNF_Minimizer::delUnness()
{
    if (resolves(exp))
    {
        logs<<"\n";
        logs <<"%Result\n";
        logs<<"1";
        exp.clear();
        Operand op;
        op.variables.push_back(Variable("1", false));
        exp.push_back(op);
        return;
    }

    if(exp.size()<3 || exp[0].variables.size()==1)    //la nessessity chek は　nenuzhna costille
    {
        return;
    }
    if(exp.size()<=1)
    {
        logs << "\n";
        logs <<"%Result\n";
        log(exp);
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
    logs<<"\n";
    logs <<"%Result\n";
    log(exp);
}
// NECESSITY CHECK
bool SNF_Minimizer::checkNecessity(int index)
{
    Expression resexp;  //result of inop check
    resexp.clear();

    for(int i=0; i<(int)exp.size();i++)                         // each operand except exp[index]
    {
        if(i!=index)
        {
            Operand resop;  //part of resexp
            resop.variables.clear();
            for(int j=0; j<(int)exp[i].variables.size();j++)              //each variable there
            {
                INOP_type type = inop(exp[i].variables[j], exp[index]);
                if(type==invIN) //if there is 0 in operand
                {
                    resop.variables.clear();
                    break;
                }else if(type==NIN) //if trere's a var of unknown value
                {
                    resop.variables.push_back(exp[i].variables[j]);
                }
            }
            if(!resop.variables.empty())
            {
                bool isherealready=false;
                for(Operand o : resexp)
                {
                    if(o==resop) isherealready=true;
                }

                if(!isherealready) resexp.push_back(resop); //add resop to resexp only if it's unique. needed for resolve below
            }
        }
    }
    //log(resexp);
    if(resexp.size()>1 && resolves(resexp)) //resolve NINs if there are many
    {
        return false;
    }
    return true;
}

bool SNF_Minimizer::resolves(Expression& expression)
{
    sortres(0,(int)(expression.size()-1),expression);
    for(int i=0; i<(int)expression.size(); i++)     //every operand in rank order
    {
        int j=0;
        int matches=0;                          //the number of 1rank ops that suit. should be equal to checked op size

        while(expression[j].variables.size()==1) //only 1 rank operands suit
        {
            if(i!=j) //except operand we check
            {
                if(inop(expression[j].variables[0], expression[i])==invIN) matches++; //res[j] is an inv version of some var in res[i] we check
                if(matches==(int)expression[i].variables.size())
                {
                    return true;
                }
            }
            j++;
        }
    }
    return false;
}

//qsort for res
void SNF_Minimizer::sortres(int left, int right, Expression& res)
{
    int l = left;
    int r = right;
    int x = res[(l+r)/2].variables.size();

    do{
        while((int)res[l].variables.size()<x) l++;
        while((int)res[r].variables.size()>x) r--;

        if(l<=r)
        {
            if(res[l].variables.size()>res[r].variables.size())
            {
                swap(res[l], res[r]);
            }
            l++;
            r--;
        }
    }while(l<=r);

    if(l<right) sortres(l, right, res);
    if(r>left)  sortres(left, r, res);
}

// INOP
INOP_type SNF_Minimizer::inop(Variable &var, Operand &op)
{
    for(int i=0; i<(int)op.variables.size(); i++)
    {
        if(var.name==op.variables[i].name)
        {
            if(var.inversion==op.variables[i].inversion)  return IN;
            return invIN;
        }
    }
    return NIN;
}
