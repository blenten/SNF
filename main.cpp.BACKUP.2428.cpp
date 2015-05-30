#include <QApplication>
#include <fstream>
#include <string>

#include "snf_minimizer/snf_minimizer.h"
#include "snf_generator/snf_generator.h"
#include "mainwindow.h"

void expressionOutputSample(const Expression&  ex, const FunctionType& ft);

int main()
{
<<<<<<< HEAD
    QApplication app(argc, argv);

    MainWindow mwnd;
    mwnd.show();

    //FunctionVector vec;
    //SNF_Generator::generate(2,500,2,500,vec,50,50);
    //
    //std::ofstream ofs("log.txt");
    //SNF_Generator::testMinimizing(vec,std::cout); //change to ofs after testing
    //ofs.close();
    //
    //cin.clear();
    //cin.get();
    return app.exec();
=======
   FunctionVector vec;
   SNF_Generator::generate(5,5,1,5,vec);

   SNF_Minimizer min;
   for (int i=0;i<(int)vec.size();i++)
   {
      const Function &func=vec.at(i);
     std::cout <<"function with "<<func.variablesNumber<<" variables and "<<func.operandsNumber
              <<" operands minimized with time: "<<std::to_string(SNF_Generator::getTimeMinimized(vec.at(i).function))<<"ms\n";
   }
    cin.clear();
    cin.get();
    return 0;
>>>>>>> 0b1d7223024525223b75c6f2c9a2c8f5a2f1d78b
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
