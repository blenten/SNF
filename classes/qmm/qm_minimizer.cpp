#include "qm_minimizer.h"

QM_Minimizer::QM_Minimizer()
{
    parser = createParser();
    curr_exp.clear();
    opsize = -1;
}
QM_Minimizer::~QM_Minimizer()
{
    delete parser;
}



SNF_ParserFacade* QM_Minimizer::createParser()
{
    return new SNF_ParserFacade();
}
void QM_Minimizer::set_opsize(int new_size)
{
    opsize = new_size;
}
void QM_Minimizer::set_currexp(QMExp exp)
{
    if(!exp.empty())
    {
        curr_exp = exp;
    }
}

bool QM_Minimizer::inExp(QMOperand &op, QMExp &exp)
{
    for(int i=0; i<(int)exp.size(); i++)
    {
        if(exp[i].vars==op.vars)
        {
            return true;
        }
    }
    return false;
}



void QM_Minimizer::toGroups(QMExp &expression, Groups &res)
{
    if(expression.empty())
    {
        return;
    }

    res.resize(opsize+1);

    for(size_t i=0; i<expression.size(); i++)
    {
        int ones=0;
        for(int j=0; j<opsize; j++)
        {
            if(expression[i].vars[j]=='1') ones++;
        }
        res[ones].push_back(expression[i]);
    }
}

void QM_Minimizer::export_unmatched(Groups &temp, QMExp &res_exp)
{
    for(int i=0; i<(int)temp.size(); i++)
    {
        for(int j=0; j<(int)temp[i].size();j++)
        {
            if(!temp[i][j].matched)
            {
                res_exp.push_back(temp[i][j]);
            }
        }
    }
}

void QM_Minimizer::delsame(Groups &temp)
{
    QMExp texp;
    for(int i=0; i<(int)temp.size(); i++)
    {
        int j=0;
        while(j<(int)temp[i].size())
        {
            if(inExp(temp[i][j], texp))
            {
                temp[i].erase(temp[i].begin()+j);
            }else
            {
                texp.push_back(temp[i][j]);
                j++;
            }
        }
    }
}

pair<QMOperand*, int> QM_Minimizer::matchOps(QMOperand &op1, QMOperand &op2)
{
     QString res_vars;
     pair<QMOperand*, int> result;

     if(op1.vars.size()!=opsize || op2.vars.size()!=opsize) //not needed if input's correct
     {
         result.first = nullptr;
         result.second = -1;
         return result;
     }

     res_vars = op1.vars;
     bool matched_already = false;

     for(int i=0; i<opsize; i++)
     {
         if(op1.vars[i]==op2.vars[i])
         {
             continue;
         }else if(op1.vars[i]=='-' || op2.vars[i]=='-') //if '-' signs have different position in op1 and op2
         {
             result.first = nullptr;
             result.second = -1;
             return result;
         }else
         {
             if(matched_already)
             {
                 result.first = nullptr;
                 result.second = -1;
                  return result;
             }

             res_vars[i] = '-';
             matched_already = true;
             result.second = i;
         }
     }
     result.first = new QMOperand(res_vars);
     return result;
}

void QM_Minimizer::firstMatch(QMExp &match_exp, Groups &match_groups)
{

    Groups temp = match_groups;
    match_groups.clear();
    match_groups.resize(opsize);
    bool anymatch = false; // for costille


    QMOperand *match_resop = nullptr;
    for(size_t i=0; i<(temp.size()-1); i++)
    {
        for(size_t j=0; j<temp[i].size(); j++)
        {
            for(size_t k=0; k<temp[i+1].size(); k++)
            {
                int match_i;
                std::tie(match_resop, match_i) = matchOps(temp[i][j], temp[i+1][k]);
                if(match_resop!=nullptr)
                {
                    match_groups[match_i].push_back(*match_resop);
                    temp[i][j].matched = true;
                    temp[i+1][k].matched = true;
                    delete match_resop;
                    anymatch = true;
                }
            }
        }
    }
    export_unmatched(temp, match_exp);

    // la secMatch cycle not to start if useless cotsille
    if(!anymatch)
    {
        match_groups.clear();
    }
}

void QM_Minimizer::secMatch(QMExp &match_exp, Groups &match_groups)
{
    if(match_groups.empty()) return;

    Groups temp = match_groups;
    match_groups.clear();
    match_groups.resize(opsize);
    bool anymatch = false; // for costille

    //matches in prematched groups
    if(match_groups.size()>1)
    {
        QMOperand *match_resop = nullptr;

        for(size_t i=0; i<temp.size(); i++)
        {
            for(int j=0; j<(int)temp[i].size()-1; j++)
            {
                for(int k=j+1; k<(int)temp[i].size();k++)
                {
                    int match_i;
                    std::tie(match_resop, match_i) = matchOps(temp[i][j], temp[i][k]);
                    if(match_resop!=nullptr)
                    {
                        match_groups[match_i].push_back(*match_resop);
                        temp[i][j].matched = true;
                        temp[i][k].matched = true;
                        delete match_resop;
                        anymatch = true;
                    }
                }
            }
        }
    }

    // adds unmatched or single ops to result expression
    export_unmatched(temp, match_exp);

    // la endless secMatch cotsille
    if(!anymatch)
    {
        match_groups.clear();
    }
}

QMExp QM_Minimizer::match(QMExp &match_exp)
{
    if(opsize==-1)
    {
        set_opsize(match_exp[0].vars.size());
    }
    QMExp res;
    Groups temp;
    toGroups(match_exp, temp);
    firstMatch(res, temp);
    delsame(temp);
    while(!temp.empty())
    {
        secMatch(res, temp);
        delsame(temp);
    }
    return res;
}



bool QM_Minimizer::covers(QMOperand &matched_op, QMOperand &input_op)
{
    for(int i=0; i<matched_op.vars.size(); i++)
    {
        if(matched_op.vars[i]!='-' && matched_op.vars[i]!=input_op.vars[i])
        {
            return false;
        }
    }
    return true;
}

//QMExp QM_Minimizer::cutCore(QMExp matched_ops, QMExp input_ops)
//{
//    return "XYN";
//}
