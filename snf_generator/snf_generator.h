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
    static std::string generateFunction (unsigned int number, FunctionType ft);

public:
    //generates vector of functions (with variables number from down to up value) in FunctionVector
    //each function will contain FIXME adds
    static void generate (unsigned int downVariablesNumber, unsigned int upVariablesNumber, FunctionVector& vec);

};



#endif
