#include "snf_generator.h"

void SNF_Generator::generate(unsigned int downVariablesNumber, unsigned int upVariablesNumber, unsigned int downOperandsNumber, unsigned int upOperandsNumber, FunctionVector &vec)
{
    srand (QDateTime::currentMSecsSinceEpoch());
    for (unsigned int i=downVariablesNumber;i<=upVariablesNumber;i++)
    {
       for (unsigned int operandNumber=downOperandsNumber;operandNumber<=upOperandsNumber; operandNumber++)
       {
           Function func;
           func.operandsNumber=operandNumber;
           func.variablesNumber=i;
           if(getRandom(1)) func.function=generateFunction(i,operandNumber, SNDF);
           else func.function=generateFunction(i,operandNumber, SNKF);

           vec.push_back(func);
       }
    }
}

int SNF_Generator::getRandom(int max)
{
    return rand()%(max+1);
}

std::string SNF_Generator::generateFunction(unsigned int number, unsigned int operandNumber, FunctionType ft)
{
    std::vector <std::string> usedVariables;
    for(unsigned int i=1;i<=number;i++) usedVariables.push_back("x"+std::to_string(i));

    std::string output="";

    for (unsigned int i=0;i<operandNumber;i++)
    {
        output+="(";
        for (unsigned int j=0;j<number;j++)
        {
            if (getRandom(1))output+="!";
            output+=usedVariables.at(j);
            if(j!=number-1)
            {
                if (ft) output+="*";
                else output+="+";
            }
        }
        output+=")";
        if (i!=operandNumber-1)
        {
            if (ft)output+="+";
            else output+="*";
        }
    }
    return output;
}


unsigned long SNF_Generator::getTimeMinimized (std::string function)
{
    unsigned long time = QDateTime::currentMSecsSinceEpoch();
    SNF_Minimizer min;
    min.minimize(function);
    time=QDateTime::currentMSecsSinceEpoch()-time;
    return time;
}
