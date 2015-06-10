#ifndef SNF_GENERATOR_H
#define SNF_GENERATOR_H
#include "../snf_minimizer/snf_minimizer.h"
#include <QDateTime>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <omp.h>

class SNF_Generator
{
private:
    static int getRandom (int max);
    static double getTimeMinimized (std::string function);

    //replacement of mother-returning function in Minimizer class
    static std::string minimize (std::string function);

public:

    //gets time of minimizing functions; writes a log to file on path; prints an completing info to infoOutputStream
    static void testMinimizing (std::string path,unsigned int downVariablesNumber,
                                unsigned int upVariablesNumber, unsigned int downOperandsNumber,
                                unsigned int upOperandsNumber, unsigned int variablesStep=1,
                                unsigned int operandsStep=1, std::ostream &infoOutputStream=std::cout);

    static std::string generateFunction (unsigned int number, unsigned int operandNumber,FunctionType ft);

};

#endif
