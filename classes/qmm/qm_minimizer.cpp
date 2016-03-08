#include "qm_minimizer.h"

QM_Minimizer::QM_Minimizer()
{
    parser = createParser();
    exp.clear();
}
QM_Minimizer::~QM_Minimizer()
{
    delete parser;
}



SNF_ParserFacade* QM_Minimizer::createParser()
{
    return new SNF_ParserFacade();
}



void QM_Minimizer::toGroups(QMExp &expression, Groups &res)
{
    if(expression.empty())
    {
        return;
    }

    res.resize(expression[0].vars.size()+1);

    for(size_t i=0; i<expression.size(); i++)
    {
        int ones=0;
        for(int j=0; j<expression[i].vars.size(); j++)
        {
            if(expression[i].vars[j]=='1') ones++;
        }
        res[ones].push_back(expression[i]);
    }
}

void QM_Minimizer::firstMatch(QMExp &match_exp, Groups &res)
{
    Groups temp;
    toGroups(match_exp, temp);
    match_exp.clear();
    res.resize(match_exp[0].vars.size());

    QMOperand *match_resop = nullptr;
    for(size_t i=0; i<(temp.size()-1); i++)
    {
        for(size_t j=0; j<temp[i].size(); j++)
        {
            for(size_t k=0; k<temp[i+1].size(); k++)
            {
                int match_i;
                match_resop = matchOps(temp[i][j], temp[i+1][k], match_i);
                if(match_resop!=nullptr)
                {
                    res[match_i].push_back(*match_resop);
                    temp[i][j].matched = true;
                    temp[i+1][k].matched = true;
                    delete match_resop;
                }
            }
        }
    }
    for(size_t i=0; i<temp.size(); i++)
    {
        for(size_t j=0; j<temp[i].size();j++)
        {
            if(!temp[i][j].matched)
            {
                match_exp.push_back(temp[i][j]);
            }
        }
    }
}

QMOperand* QM_Minimizer::matchOps(QMOperand &op1, QMOperand &op2, int &match_index)
{
     if(op1.vars.size() != op2.vars.size()) //not needed if input's correct
     {
         match_index = -1;
         return nullptr;
     }
     QString res;
     res = op1.vars;
     bool matched_already = false;

     for(int i=0; i<op1.vars.size(); i++)
     {
         if(op1.vars[i]==op2.vars[i])
         {
             continue;
         }else if(op1.vars[i]=='-' || op2.vars[i]=='-')
         {
             match_index = -1;
             return nullptr;
         }else
         {
             if(matched_already)
             {
                 match_index = -1;
                 return nullptr;
             }

             res[i] = '-';
             matched_already = true;
             match_index = i;
         }
     }

     return new QMOperand(res);
}
