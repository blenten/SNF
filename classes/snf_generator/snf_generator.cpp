#include "snf_generator.h"
std::ofstream SNF_Generator::logStream;
std::ostream* SNF_Generator::infoStream;
std::vector <std::string> SNF_Generator::generatedOperands;

void SNF_Generator::testMinimizing(std::string logPath,
                                   unsigned int downVariablesNumber, unsigned int upVariablesNumber,
                                   unsigned int downOperandsNumber, unsigned int upOperandsNumber,
                                   unsigned int variablesStep, unsigned int operandsStep,
                                   std::ostream &infoOutputStream)
{
    logStream.open(logPath);
    infoStream=&infoOutputStream;
    generatedOperands.clear();

    (*infoStream)<<"Testing...\n";

    double stepsCount = (ceil((double)(upVariablesNumber-downVariablesNumber+1)/(double)variablesStep) * ceil(((double)(upOperandsNumber-downOperandsNumber+1)/(double)operandsStep)));
    double doneStepsCount=0;

    SNF_Generator::logHead();

    srand (QDateTime::currentMSecsSinceEpoch());
    for (unsigned int i=downVariablesNumber;i<=upVariablesNumber;i+=variablesStep)
    {
        for (unsigned int j=downOperandsNumber;j<=upOperandsNumber;j+=operandsStep)
        {
            std::string func;
            if(getRandom(1)) func=generateFunction(i,j, SNDF);
            else func=generateFunction(i,j, SNKF);

            SNF_Generator::logCurrentFunction(i, j, SNF_Generator::getMinimizingTime(func));

            doneStepsCount++;
            SNF_Generator::logPercentCompleted(doneStepsCount/stepsCount*100);
        }
    }
    logStream.close();
}

int SNF_Generator::getRandom(int max)
{
    return rand()%(max+1);
}

std::string SNF_Generator::generateFunction(unsigned int variablesNumber, unsigned int operandsNumber, FunctionType ft)
{
    std::string output="";

    for (unsigned int i=0; i<operandsNumber; i++)
    {
        output+="(";
        for (unsigned int j=0; j<variablesNumber; j++)
        {
           output+= SNF_Generator::generateOperand(j, variablesNumber, ft);
        }
        output += ")";
        if (i != operandsNumber-1)
        {
            if (ft==SNDF) output += "+";
            else output += "*";
        }
    }
    std::cerr<<ft<<" "<<output<<"\n";
    return output;
}

std::string SNF_Generator::generateOperand(int currentVariablesNumber, int variablesNumber, FunctionType ft)
{
    std::string output;
    do
    {
        output="";
        if (getRandom(1)) output += "!";
        output += ("x"+std::to_string(currentVariablesNumber+1));

        if(currentVariablesNumber != variablesNumber-1)
        {
            if (ft==SNDF) output += "*";
            else output += "+";
        }
    }
    while (SNF_Generator::isOperandRepeat(output) && generatedOperands.size()<= currentVariablesNumber*currentVariablesNumber);//temp

    generatedOperands.push_back(output);
    return output;
}

bool SNF_Generator::isOperandRepeat(string operand)
{
    size_t size = generatedOperands.size();
    for (size_t i = 0; i<size; i++)
        if (generatedOperands[i] == operand) return true;
    return false;
}

double SNF_Generator::getMinimizingTime (std::string function)
{
    double time = omp_get_wtime();
    SNF_Generator::minimize(function);
    time=omp_get_wtime()-time;
    return time;
}

std::string SNF_Generator::minimize(string function)
{
    SNF_Minimizer snf;
    if(snf.parse(function))
        return "";

    snf.match();
    snf.delNeedless();
    return snf.res_toString();
}

void SNF_Generator::logHead()
{
    logStream<<"variables\toperands\ttime\n";
}

void SNF_Generator::logCurrentFunction (int currentVariablesNumber, int currentOperandsNumber, double currentTime)
{
    logStream<<std::setw(9)<<currentVariablesNumber<<"\t";
    logStream<<std::setw(8)<<currentOperandsNumber<<"\t";
    logStream<< std::to_string(currentTime)<<"s\t\n";
}

void SNF_Generator::logPercentCompleted(double percent)
{
    (*infoStream) <<"\r                 \rReady: "<<percent<<"%";
    infoStream->flush();
}
