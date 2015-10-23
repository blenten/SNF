#ifndef SNF_TESTER_H
#define SNF_TESTER_H
#include "../snf_minimizer/snf_minimizer.h"
#include <QDateTime>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <QElapsedTimer>
#include <QObject>

class SNF_Tester: public QObject
{    
    Q_OBJECT

private:
    std::ofstream logStream;

    double stepsCount;
    bool isStopped;

    std::vector<std::string> generatedOperands;
    std::vector <quint64> maxOperandsNumbers; //max numbers of operands for each variables number to avoid repeating (equals 2 to the number power)

    bool checkRanges();

    void getMaxOperandsNumbers();
    void getStepsCount();

    void testMinimizing();

    int getRandom (int max);
    double getMinimizingTime (std::string function);

    //replacement of mother-returning function in Minimizer class
    std::string minimize (std::string function);

    void logHead();
    void logCurrentFunction (int currentVariablesNumber, int currentOperandsNumber, double currentTime);
    void logInfoPercentCompleted(double percent);

    std::string generateOperand(quint64 variablesNumber, FunctionType ft);
    bool isOperandRepeated (std::string operand);

public:
    unsigned int downVariablesNumber;
    unsigned int upVariablesNumber;
    unsigned int variablesStep;
    unsigned int downOperandsNumber;
    unsigned int upOperandsNumber;
    unsigned int operandsStep;
    std::string logPath;

    std::string generateFunction (quint64 variablesNumber, quint64 operandsNumber, FunctionType ft);

signals:
    void onInfoSend(QString info);
    void finish();

public slots:
    //gets time of minimizing functions; writes a log to file on path; prints an completing info to infoOutputStream
    void start();
    void stop();
};

#endif
