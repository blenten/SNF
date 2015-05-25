#ifndef SNF_GENERATOR_H
#define SNF_GENERATOR_H
#include "../snf_minimizer/snf_minimizer.h"

typedef std::vector<std::string> FunctionVector;

class SNF_Generator
{
private:
    int getRandom (int down, int up);

public:
    //generates vector of functions (with variables number from down to up value) in FunctionVector
    static void generate (unsigned int downVariablesNumber, unsigned int upVariablesNumber, FunctionVector& vec);

};



#endif
