#include "qm_minimizer.h"

QM_Minimizer::QM_Minimizer()
{
    parser = createParser();
}
QM_Minimizer::~QM_Minimizer()
{
    delete parser;
}
SNF_ParserFacade* QM_Minimizer::createParser()
{
    return new SNF_ParserFacade();
}


QMOperand* QM_Minimizer::matchOps(QMOperand &op1, QMOperand &op2)
{
     if(op1.vars.size() != op2.vars.size()) //not needed if input's correct
     {
         return nullptr;
     }
     QString res;
     res = op1.vars;
     bool matched_already = false;

     for(int i=0; i<(int)op1.vars.size(); i++)
     {
         if(op1.vars[i]==op2.vars[i])
         {
             continue;
         }else if(op1.vars[i]=='-' || op2.vars[i]=='-')
         {
             return nullptr;
         }else
         {
             if(matched_already)
             {
                 return nullptr;
             }

             res[i] = '-';
             matched_already = true;
         }
     }

     return new QMOperand(res);
}
