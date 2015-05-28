#ifndef SNF_GENERATOR_H
#define SNF_GENERATOR_H
#include "../snf_minimizer/snf_minimizer.h"
#include <QDateTime>
#include <cstdlib>
#include <iomanip>

struct Function
{
    std::string function;
    int variablesNumber, operandsNumber;
};

typedef std::vector<Function> FunctionVector;

class SNF_Generator
{
private:
    static int getRandom (int max);
    static std::string generateFunction (unsigned int number, unsigned int operandNumber,FunctionType ft);
    static unsigned long getTimeMinimized (std::string function);

public:
    //generates vector of functions (with variables number from down to up value) in FunctionVector
    //each function will be with operands number from down to up value
    static void generate (unsigned int downVariablesNumber, unsigned int upVariablesNumber,
                          unsigned int downOperandsNumber, unsigned int upOperandsNumber,
                          FunctionVector& vec, unsigned int variablesStep=1, unsigned int operandsStep=1);

    //gets time of minimizing functions and writes a log to output stream
    static void testMinimizing (FunctionVector& vec, std::ostream& os);

};



#endif
