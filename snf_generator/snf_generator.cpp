#include "snf_generator.h"

void SNF_Generator::generate(unsigned int downVariablesNumber, unsigned int upVariablesNumber, FunctionVector &vec)
{
    srand (QDateTime::currentMSecsSinceEpoch());
    for (unsigned int i=downVariablesNumber;i<=upVariablesNumber;i++)
    {
       if(getRandom(1)) vec.push_back(generateFunction(i, SNDF));
       else vec.push_back(generateFunction(i, SNKF));
    }
}


int SNF_Generator::getRandom(int max)
{
    return rand()%(max+1);
}


std::string SNF_Generator::generateFunction(unsigned int number, FunctionType ft)
{
    std::vector <std::string> usedVariables;
    for(unsigned int i=1;i<=number;i++) usedVariables.push_back("x"+std::to_string(i));

    std::string output="";

    unsigned int addNumber=5; //TODO

    for (unsigned int i=0;i<addNumber;i++)
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
        if (i!=addNumber-1)
        {
            if (ft)output+="+";
            else output+="*";
        }
    }

    return output;
}

