#include "snf_minimizer/snf_minimizer.h"
#include "snf_generator/snf_generator.h"

#include <string>

void expressionOutputSample(const Expression&  ex, const FunctionType& ft);

int main(int argc, char *argv[])
{
   FunctionVector vec;
   SNF_Generator::generate(100,150,100,101,vec);

   SNF_Minimizer min;
   for (int i=0;i<vec.size();i++)
   {
      const Function &func=vec.at(i);
     std::cout <<"function with "<<func.variablesNumber<<" variables and "<<func.operandsNumber
              <<" operands minimized with time: "<<std::to_string(SNF_Generator::getTimeMinimized(vec.at(i).function))<<"ms\n";
   }

    cin.clear();
    cin.get();
    return 0;
}













///this was in main.cpp
/*  SNF_Minimizer snf;
  string result;
  //result = snf.minimize("(x1+x2+x3)(!x1+x2+x3)(!x1+!x2+x3)(!x1+!x2+!x3)"); ///commented MUHAHAHAHAHA
  result=snf.minimize("x1!!!!x2+ !x1*x2");
  cout<<"RES: "<<result<<endl;
*/


///You really don't need to comment this
// YAP :p

///motherfucker
/*
void expressionOutputSample(const Expression&  ex, const FunctionType &ft)
{

    switch(ft)
    {

        case OTHER: std::cout <<"OTHER\n"; break;
        case SNDF: std::cout <<"SNDF\n"; break;
        case SNKF: std::cout << "SNKF\n"; break;
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

*/
