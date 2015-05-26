#ifndef SNF_GENERATOR_H
#define SNF_GENERATOR_H
#include "../snf_minimizer/snf_minimizer.h"
#include <QDateTime>
#include <cstdlib>

typedef std::vector<std::string> FunctionVector;

class SNF_Generator
{
private:
    static int getRandom (int max);
    static std::string generateFunction (unsigned int number, unsigned int operandNumber,FunctionType ft);

public:
    //generates vector of functions (with variables number from down to up value) in FunctionVector
    //each function will be with operands number from down to up value
    static void generate (unsigned int downVariablesNumber, unsigned int upVariablesNumber,
                          unsigned int downOperandsNumber, unsigned int upOperandsNumber, FunctionVector& vec);

};



#endif
