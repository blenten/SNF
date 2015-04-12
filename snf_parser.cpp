#include "snf_parser.h"

SNF_Parser::SNF_Parser()
{

}


FunctionType SNF_Parser::parse(std::string input, Expression &output)
{
    if (input.length()==0) return OTHER;
    _input=input;
    std::vector <std::string> variables;
   // getVariables(input, variables);
    std::cout <<checkBrackets();
}

int SNF_Parser::getSymbolType(char symb)
{
    if (symb=='(') return SYMBOL_LBRACKET;
    if (symb==')') return SYMBOL_RBRACKET;
    if (symb=='&' || symb=='*') return SYMBOL_CONJUNCTION;
    if (symb=='|' || symb=='+') return SYMBOL_DISJUNCTION;
    if (symb=='!' || symb=='-') return SYMBOL_INVERSE;
    if (isdigit(symb)||isalpha(symb)) return SYMBOL_OPERAND;
    if (symb==' ') return SYMBOL_SPACE;
    if (symb=='\0') return SYMBOL_ZERO;

    return SYMBOL_OTHER;
}


int SNF_Parser::getVariables(std::vector<std::string> &variables)
{
    std::string currVar="";

    size_t len=_input.length();

    int currIndex=0;
    int varNumber=0;

    currVar="";

    while (!_input[currIndex])
        ;

    std::cout <<currVar<<"\n";

}


  bool SNF_Parser::checkBrackets()
  {
    int len=_input.length();
    int lCount=0, rCount=0;
    for (int i=0;i<len+1;i++)
    {
        if (getSymbolType(_input[i])==SYMBOL_RBRACKET)
        {
            if (lCount<=rCount) return false;
            rCount++;
        }
        else if (getSymbolType(_input[i])==SYMBOL_LBRACKET)
            lCount++;
    }
    if (lCount==rCount) return true;
    return false;
  }

