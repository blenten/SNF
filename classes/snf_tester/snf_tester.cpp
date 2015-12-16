/**
  \file
*/

#include "snf_tester.h"

void SNF_Tester::start()
{
    isStopped=false;
    if (checkRanges())
    {
        onInfoSend("Testing...\n");

        getMaxOperandsNumbers();
        getStepsCount();
        testMinimizing();
    }
    else emit onInfoSend("Too big value.");
    emit finish();
}

void SNF_Tester::stop()
{
    isStopped=true;
}

bool SNF_Tester::checkRanges()
{
    if (upVariablesNumber > sizeof(quint64)*8 - 1) return false;
    return true;
}

void SNF_Tester::getMaxOperandsNumbers()
{
    maxOperandsNumbers.clear();
    for (quint64 i=downVariablesNumber; i<=upVariablesNumber; i+=variablesStep)
    {
        quint64 maxOperandsNumber = pow (2,i);
        if (maxOperandsNumber > upOperandsNumber) maxOperandsNumber = upOperandsNumber;
        maxOperandsNumbers.push_back(maxOperandsNumber);
    }
}

void SNF_Tester::getStepsCount()
{
    stepsCount=0;
    quint64 size = maxOperandsNumbers.size();
    for (quint64 i=0; i<size; i++)
    {
       stepsCount += ceil((double)(maxOperandsNumbers[i]-downOperandsNumber+1)/(double)operandsStep);
    }
}

void SNF_Tester::testMinimizing()
{
    logHead();

    srand (QDateTime::currentMSecsSinceEpoch());
    quint64 index=0;
    double doneStepsCount=0;
    for (quint64 i=downVariablesNumber; i<=upVariablesNumber; i+=variablesStep)
    {
        quint64 maxOperandsNumber = maxOperandsNumbers[index++];

        for (quint64 j=downOperandsNumber; j<=maxOperandsNumber; j+=operandsStep)
        {
            if (isStopped)
            {
                emit onInfoSend("Stopped.");
                return;
            }

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

std::string SNF_Tester::generateFunction(quint64 variablesNumber, quint64 operandsNumber, FunctionType ft)
{
    std::string output = "";
    generatedOperands.clear();

    for (quint64 i=0; i<operandsNumber; i++)
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

std::string SNF_Tester::generateOperand(quint64 variablesNumber, FunctionType ft)
{
    std::string output;
    do
    {
        output = "";
        for (quint64 i=0; i<variablesNumber; i++)
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
    quint64 size = generatedOperands.size();
    for (quint64 i = 0; i<size; i++)
        if (generatedOperands[i] == operand) return true;
    return false;
}

double SNF_Tester::getMinimizingTime (std::string function)
{
    QElapsedTimer timer;
    timer.start();
    SNF_Tester::minimize(function);
    return ((double)timer.nsecsElapsed()/1000000000.0); //to seconds
}

std::string SNF_Tester::minimize(string function)
{
    SNF_Minimizer snf;
    if(snf.parse(function))
        return "";

    snf.match();
    snf.delUnness();
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
    onInfoSend("Ready: "+ QString::number(percent) + "%");
}
