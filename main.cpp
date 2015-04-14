#include <QCoreApplication>
#include "snf_parser.h"

int main(int argc, char *argv[])
{
    SNF_Parser parser;
    Expression ex;
    std::string input="x1*x2*x3+x1*!x2*x3";

    std::string test="y+(x)";



FunctionType ft= parser.parse(test,ex);


switch(ft)
{

    case OTHER: std::cout <<"OTHER\n"; break;
    case SDNF: std::cout <<"SDNF\n"; break;
    case SKNF: std::cout << "SKNF\n"; break;
}

    return 0;
}
