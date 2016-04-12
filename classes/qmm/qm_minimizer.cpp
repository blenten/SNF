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
    QMExp res;
    if(match_exp.empty())
    {
        res.clear();
        return res;
    }
    if(opsize==-1)
    {
        set_opsize(match_exp[0].vars.size());
    }
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

QMExp QM_Minimizer::get_covered(QMOperand &matched_op, QMExp &input_ops)
{
    QMExp res;
    res.clear();

    for(int i=0; i<(int)input_ops.size(); i++)
    {
        if(covers(matched_op, input_ops[i]))
        {
            res.push_back(input_ops[i]);
        }
    }
    return res;
}

void QM_Minimizer::del_covered(QMOperand &matched_op, QMExp &input_ops)
{
    int i = 0;
    while(i<(int)input_ops.size())
    {
        if(covers(matched_op, input_ops[i]))
        {
            input_ops.erase(input_ops.begin()+i);
        }else
        {
            i++;
        }
    }
}

QMExp QM_Minimizer::cutCore(QMExp &matched_ops, QMExp &input_ops)
{
    QMExp core;
    core.clear();
    for(int i=0; i<(int)input_ops.size(); i++)
    {
        int match_ops_cover = 0;
        int cover_index = -1; //for only 1 cover case

        for(int j=0; j<(int)matched_ops.size(); j++)
        {
            if(covers(matched_ops[j], input_ops[i]))
            {
                match_ops_cover++;
                cover_index = j;
            }
        }
        if(match_ops_cover==1)
        {
            core.push_back(matched_ops[cover_index]);
            matched_ops.erase(matched_ops.begin()+cover_index);
        }
    }

    for(int i=0; i<(int)core.size(); i++)
    {
        del_covered(core[i], input_ops);
    }
    return core;
}

void QM_Minimizer::sort_implicants(QMExp &matched_ops, vector<int> &rating, int first, int last)
{
    int f = first;
    int l = last;
    int x = rating[(f+l)/2];

    do{
        while(rating[f]>x) f++;
        while(rating[l]<x) l--;

        if(f<=l)
        {
            if(rating[f]<rating[l])
            {
                swap(rating[f], rating[l]);
                swap(matched_ops[f], matched_ops[l]);
            }
            f++;
            l--;
        }
    }while(f<=l);

    if(f<last) sort_implicants(matched_ops, rating, f, last);
    if(l>first) sort_implicants(matched_ops, rating, first, l);
}

void QM_Minimizer::del_dupl_implicants(QMExp &matched_ops, QMExp &input_ops)
{
    for(int i=0; i<(int)matched_ops.size()-1; i++)
    {
        QMExp f_covered = get_covered(matched_ops[i], input_ops);
        int j=1+i;
        while( j<(int)matched_ops.size())
        {
            QMExp s_covered = get_covered(matched_ops[j], input_ops);
            if(f_covered==s_covered)
            {
                matched_ops.erase(matched_ops.begin()+j);
            }else
            {
                j++;
            }
        }
    }
}

QMExp QM_Minimizer::get_Optimal_Impl(QMExp &matched_ops, QMExp &input_ops)
{
    QMExp res;
    res.clear();

    vector<int> rating;
    rating.resize(matched_ops.size());
    for(int i=0; i<(int)rating.size(); i++)
    {
        rating[i] = 0;
    }

    for(int i=0; i<(int)matched_ops.size(); i++)
    {
        for(int j=0; j<(int)input_ops.size(); j++)
        {
            if(covers(matched_ops[i], input_ops[j]))
            {
                rating[i]++;
            }
        }
        for(int j=0; j<(int)matched_ops[i].vars.size(); j++)
        {
            if(matched_ops[i].vars[j]=='-')
            {
                rating[i]++;
            }
        }
    }
    sort_implicants(matched_ops, rating, 0, (int)matched_ops.size()-1);
    del_dupl_implicants(matched_ops, input_ops);
    while(!input_ops.empty() && !matched_ops.empty())
    {
        del_covered(matched_ops[0], input_ops);
        res.push_back(matched_ops[0]);
        matched_ops.erase(matched_ops.begin());
    }
    return res;
}
