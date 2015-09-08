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

    unsigned int downVariablesNumber;
    unsigned int upVariablesNumber;
    unsigned int variablesStep;
    unsigned int downOperandsNumber;
    unsigned int upOperandsNumber;
    unsigned int operandsStep;

    double stepsCount;

    std::ofstream logStream;
    std::ostream* infoStream;

    std::vector<std::string> generatedOperands;
    std::vector <int> maxOperandsNumbers; //max numbers of operands for each variables number to avoid repeating

    void getMaxOperandsNumbers();
    void getStepsCount();

    int getRandom (int max);
    double getMinimizingTime (std::string function);

    //replacement of mother-returning function in Minimizer class
    std::string minimize (std::string function);

    void logHead();
    void logCurrentFunction (int currentVariablesNumber, int currentOperandsNumber, double currentTime);
    void logPercentCompleted(double percent);

    std::string generateOperand(unsigned int variablesNumber, FunctionType ft);
    bool isOperandRepeat (std::string operand);

public:

    //gets time of minimizing functions; writes a log to file on path; prints an completing info to infoOutputStream
    void testMinimizing (std::string logPath,
                                unsigned int _downVariablesNumber, unsigned int _upVariablesNumber,
                                unsigned int _downOperandsNumber, unsigned int _upOperandsNumber,
                                unsigned int _variablesStep=1, unsigned int _operandsStep=1,
                                std::ostream &infoOutputStream=std::cout);

    std::string generateFunction (unsigned int variablesNumber, unsigned int operandsNumber,FunctionType ft);

};

#endif
