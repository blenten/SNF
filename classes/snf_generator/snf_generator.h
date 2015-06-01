#ifndef SNF_GENERATOR_H
#define SNF_GENERATOR_H
#include "../snf_minimizer/snf_minimizer.h"
#include <QDateTime>
#include <cstdlib>
#include <iomanip>

#include <omp.h>

class SNF_Generator
{
private:
    static int getRandom (int max);
    static double getTimeMinimized (std::string function);

public:

    //gets time of minimizing functions and writes a log to output stream
    static void testMinimizing (std::ostream& os,unsigned int downVariablesNumber,
                                unsigned int upVariablesNumber, unsigned int downOperandsNumber,
                                unsigned int upOperandsNumber, unsigned int variablesStep=1,
                                unsigned int operandsStep=1);

    static std::string generateFunction (unsigned int number, unsigned int operandNumber,FunctionType ft);

};

#endif
