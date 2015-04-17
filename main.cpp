#include "snf_minimizer/snf_minimizer.h"

#include <string.h>
void expressionOutputSample(const Expression&  ex, const FunctionType& ft);

int main(int argc, char *argv[])
{
    SNF_Minimizer snf;
    snf.minimize("x1*x2*x3 + !x1*x2*x3 + !x1*!x2*x3 + !x1*!x2*!x3");
    ///Olerapx's previous magic below

//  SNF_Minimizer snf;
//  snf.test();
  /*  SNF_Parser parser;
    Expression ex;
    std::string input="x";
    std::string input2="(x)+(y)";
    std::string test="((x1))!x2!x3+ x1*x2*x3+ !x1*x2*x3";

    FunctionType  ft=parser.parse(input,ex);
    expressionOutputSample(ex,ft);

    ft= parser.parse(input2,ex);
    expressionOutputSample(ex,ft);

*/
    return 0;
}

///You really don't need to comment this
void expressionOutputSample(const Expression&  ex, const FunctionType &ft)
{

    switch(ft)
    {

        case OTHER: std::cout <<"OTHER\n"; break;
        case SNDF: std::cout <<"SDNF\n"; break;
        case SNKF: std::cout << "SKNF\n"; break;
    }

    for (int i=0;i<ex.size();i++)
    {
        for (int j=0;j<ex[i].size();j++)
            if (ex[i][j].invertion)
            std::cout <<"!"<<ex[i][j].name<<" ";
          else std::cout<<ex[i][j].name<<" ";
        std::cout <<"\n";
    }
}


