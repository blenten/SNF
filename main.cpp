#include <QCoreApplication>
#include "snf_parser.h"

int main(int argc, char *argv[])
{
    SNF_Parser parser;
    Expression ex;
    std::string input="x1*x2*x3+x1*!x2*x3";

 //   std::string test="x(y*z)";
    std::string test="x+(y*z)";
    parser.parse(test,ex);


    return 0;
}
