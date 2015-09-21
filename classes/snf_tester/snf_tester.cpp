#include "snf_tester.h"

void SNF_Tester::start(std::string _logPath,
                                   unsigned int _downVariablesNumber, unsigned int _upVariablesNumber,
                                   unsigned int _downOperandsNumber, unsigned int _upOperandsNumber,
                                   unsigned int _variablesStep, unsigned int _operandsStep,
                                   std::ostream &infoOutputStream)
{
    logPath =_logPath;
    downVariablesNumber = _downVariablesNumber;
    upVariablesNumber = _upVariablesNumber;
    variablesStep =_variablesStep;
    downOperandsNumber = _downOperandsNumber;
    upOperandsNumber = _upOperandsNumber;
    operandsStep = _operandsStep;

    infoStream=&infoOutputStream;

    (*infoStream)<<"Testing...\n";

    getMaxOperandsNumbers();
    getStepsCount();

    testMinimizing();
}

void SNF_Tester::getMaxOperandsNumbers()
{
    maxOperandsNumbers.clear();
    for (unsigned int i=downVariablesNumber; i<=upVariablesNumber; i+=variablesStep)
    {
        unsigned int maxOperandsNumber = pow (2,i);
        if (maxOperandsNumber > upOperandsNumber) maxOperandsNumber = upOperandsNumber;
        maxOperandsNumbers.push_back(maxOperandsNumber);
    }
}

void SNF_Tester::getStepsCount()
{
    stepsCount=0;
    size_t size = maxOperandsNumbers.size();
    for (size_t i=0; i<size; i++)
    {
       stepsCount += ceil((double)(maxOperandsNumbers[i]-downOperandsNumber+1)/(double)operandsStep);
    }
}

void SNF_Tester::testMinimizing()
{
    logHead();

    srand (QDateTime::currentMSecsSinceEpoch());
    unsigned int index=0;
    double doneStepsCount=0;
    for (unsigned int i=downVariablesNumber; i<=upVariablesNumber; i+=variablesStep)
    {
        unsigned int maxOperandsNumber = maxOperandsNumbers[index++];

        for (unsigned int j=downOperandsNumber; j<=maxOperandsNumber; j+=operandsStep)
        {
            std::string func;
            if (getRandom(1)) func = generateFunction(i,j, SNDF);
            else func = generateFunction(i,j, SNKF);

            logCurrentFunction(i, j, getMinimizingTime(func));

            doneStepsCount++;
            logInfoPercentCompleted(doneStepsCount/stepsCount*100);
        }
    }
}

int SNF_Tester::getRandom(int max)
{
    return rand()%(max+1);
}

std::string SNF_Tester::generateFunction(unsigned int variablesNumber, unsigned int operandsNumber, FunctionType ft)
{
    std::string output = "";
    generatedOperands.clear();

    for (unsigned int i=0; i<operandsNumber; i++)
    {
        output += "(";
        output += generateOperand(variablesNumber,ft);
        output += ")";

        if (i != operandsNumber-1)
        {
            if (ft == SNDF) output += "+";
            else output += "*";
        }
    }
    return output;
}

std::string SNF_Tester::generateOperand(unsigned int variablesNumber, FunctionType ft)
{
    std::string output;
    do
    {
        output = "";
        for (unsigned int i=0; i<variablesNumber; i++)
        {
            if (getRandom(1)) output += "!";
            output += ("x" + std::to_string(i+1));
            if(i != variablesNumber-1)
            {
                if (ft == SNDF) output+="*";
                else output += "+";
            }
        }
    }
    while (isOperandRepeated(output));
    generatedOperands.push_back(output);
    return output;
}

bool SNF_Tester::isOperandRepeated(string operand)
{
    size_t size = generatedOperands.size();
    for (size_t i = 0; i<size; i++)
        if (generatedOperands[i] == operand) return true;
    return false;
}

double SNF_Tester::getMinimizingTime (std::string function)
{
    double time = omp_get_wtime();
    SNF_Tester::minimize(function);
    time=omp_get_wtime()-time;
    return time;
}

std::string SNF_Tester::minimize(string function)
{
    SNF_Minimizer snf;
    if(snf.parse(function))
        return "";

    snf.match();
    snf.delNeedless();
    return snf.res_toString();
}

void SNF_Tester::logHead()
{
    logStream.open(logPath);
    logStream << stepsCount << " functions will be checked\n";
    logStream << "variables\toperands\ttime\n";
    logStream.close();
}

void SNF_Tester::logCurrentFunction (int currentVariablesNumber, int currentOperandsNumber, double currentTime)
{
    logStream.open(logPath, std::ios_base::app);
    logStream << std::setw(9) << currentVariablesNumber << "\t";
    logStream << std::setw(8) << currentOperandsNumber << "\t";
    logStream << std::to_string(currentTime) << "s\n";
    logStream.close();
}

void SNF_Tester::logInfoPercentCompleted(double percent)
{
    (*infoStream) <<"\r                 \rReady: "<< percent << "%";
    infoStream->flush();
}
