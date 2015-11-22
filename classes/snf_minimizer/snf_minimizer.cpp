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
            for(int j=0; j<(int)logex[i].size(); j++)
            {
                if(logex[i][j].inversion)                
                    logs<<'!';

                logs<<logex[i][j].name;
                if (j < (int)logex[i].size()-1) logs << (expType==SNKF? "+" :"*");
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
        logs<<"%Default\n";
        return true;
    }
    logs<<"%Parsing\n";
    log(exp);
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
            if(exp[i][j].inversion==true) output += '!';
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
    unsigned int iter = 1;
    vector<Operand> temp;
    vector<bool> matched;

    do{
        temp.clear();
        matched.resize(exp.size());
        for(int i=0; i<(int)matched.size(); i++) matched[i]=false;

        for(int i=0; i<(int)exp.size()-1; i++)
        {
            int j=i+1;
            while(j<(int)exp.size())
            {
                if(eqop(exp[i],exp[j]))
                {
                    exp.erase(exp.begin()+j);
                }else
                {
                    j++;
                }
            }
        }
        if(exp[0].size()>1) //la one-var-ops match costille
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

    // la costille
    for(int i=0; i<(int)exp.size()-1; i++)
    {
        int j=i+1;
        while(j<(int)exp.size())
        {
            if(eqop(exp[i],exp[j]))
            {
                exp.erase(exp.begin()+j);
            }else
            {
                j++;
            }
        }
    }
    //+(1,2,3)
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
//OPERAND EQUALITY
bool SNF_Minimizer::eqop(Operand& op1, Operand& op2) //op equality check kostil. cause mne vpadlu delat operand classom
{
    if(op1.size()!=op2.size())  return false;

    for(int i=0; i<(int)op1.size();i++)
    {
        if(!(op1[i]==op2[i]))
        {
            return false;
        }
    }
    return true;
}

// DEL UNNESSESARY
void SNF_Minimizer::delUnness()
{
    if(exp.size()<3 || exp[0].size()==1)    //la nessessity chek は　nenuzhna costille
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
            resop.clear();
            for(int j=0; j<(int)exp[i].size();j++)              //each variable there
            {
                INOP_type type = inop(exp[i][j], exp[index]);
                if(type==invIN) //if there is 0 in operand
                {
                    resop.clear();
                    break;
                }else if(type==NIN) //if trere's a var of unknown value
                {
                    resop.push_back(exp[i][j]);
                }
            }
            if(!resop.empty())
            {
                bool isherealready=false;
                for(Operand o : resexp)
                {
                    if(eqop(o,resop)) isherealready=true;
                }

                if(!isherealready) resexp.push_back(resop); //add resop to resexp only if it's unique. needed for resolve below
            }
        }
    }
    //log(resexp);
    if(resexp.size()>1) //resolve NINs if there are many
    {
        sortres(0,(int)(resexp.size()-1),resexp);
        for(int i=0; i<(int)resexp.size(); i++)     //every operand in rank order
        {
            int j=0;
            int matches=0;                          //the number of 1rank ops that suit. should be equal to checked op size

            while(resexp[j].size()==1) //only 1 rank operands suit
            {
                if(i!=j) //except operand we check
                {
                    if(inop(resexp[j][0], resexp[i])==invIN) matches++; //res[j] is an inv version of some var in res[i] we check
                    if(matches==(int)resexp[i].size())
                    {
                        return false;                        
                    }
                }
                j++;
            }
        }
    }
    return true;
}
//qsort for res
void SNF_Minimizer::sortres(int left, int right, Expression& res)
{
    int l = left;
    int r = right;
    int x = res[(l+r)/2].size();

    do{
        while((int)res[l].size()<x) l++;
        while((int)res[r].size()>x) r--;

        if(l<=r)
        {
            if(res[l].size()>res[r].size())
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
    for(int i=0; i<(int)op.size(); i++)
    {
        if(var.name==op[i].name)
        {
            if(var.inversion==op[i].inversion)  return IN;
            return invIN;
        }
    }
    return NIN;
}
