#include <QApplication>
#include <fstream>
#include <string>

#include "snf_minimizer/snf_minimizer.h"
#include "snf_generator/snf_generator.h"
#include "mainwindow.h"

void expressionOutputSample(const Expression&  ex, const FunctionType& ft);

int main(int argc, char* argv[])
{
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
}
