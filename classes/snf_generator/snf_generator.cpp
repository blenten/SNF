#include "snf_generator.h"

int SNF_Generator::getRandom(int max)
{
    return rand()%(max+1);
}

std::string SNF_Generator::generateFunction(unsigned int number, unsigned int operandNumber, FunctionType ft)
{
    std::string output="";

    for (unsigned int i=0;i<operandNumber;i++)
    {
        output+="(";
        for (unsigned int j=0;j<number;j++)
        {
            if (getRandom(1))output+="!";
            output+=("x"+std::to_string(j+1));
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

double SNF_Generator::getTimeMinimized (std::string function)
{
    double time = omp_get_wtime();
    SNF_Minimizer min;
    min.minimize(function);
    time=omp_get_wtime()-time;
    return time;
}

void SNF_Generator::testMinimizing(std::string path, unsigned int downVariablesNumber,
                                   unsigned int upVariablesNumber, unsigned int downOperandsNumber,
                                   unsigned int upOperandsNumber, unsigned int variablesStep,
                                   unsigned int operandsStep, std::ostream &infoOutputStream)
{
    std::ofstream os(path);
    os<<"variables\toperands\ttime\n";
    os.close();

    infoOutputStream<<"Testing...\n";

    double count = (ceil((double)(upVariablesNumber-downVariablesNumber+1)/(double)variablesStep) * ceil(((double)(upOperandsNumber-downOperandsNumber+1)/(double)operandsStep)));
    double curr=0;

    srand (QDateTime::currentMSecsSinceEpoch());

    for (unsigned int i=downVariablesNumber;i<=upVariablesNumber;i+=variablesStep)
    {
        for (unsigned int j=downOperandsNumber;j<=upOperandsNumber;j+=operandsStep)
        {
            os.open(path, std::ios_base::app);
            std::string func;
            if(getRandom(1)) func=generateFunction(i,j, SNDF);
            else func=generateFunction(i,j, SNKF);

            os<<std::setw(9)<<i<<"\t";
            os<<std::setw(8)<<j<<"\t";
            os<< std::to_string(SNF_Generator::getTimeMinimized(func))<<"ms\t\n";
            os.close();

            curr++;
            infoOutputStream <<"\r                 \rReady: "<<curr/count*100<<"%";
            infoOutputStream.flush();
        }
    }
}
