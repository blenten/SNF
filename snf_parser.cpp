#include "snf_parser.h"

FunctionType SNF_Parser::parse(std::string input, Expression &output)
{
    if (input.length()==0) return OTHER;
     _input=input;
     removeUnused();
   if (!checkBrackets()) return OTHER;
     std::vector <std::string> variables;
     getVariables(variables);
     for (int i=0;i<variables.size();i++)
         std::cout <<variables[i]<<" ";
     std::cout<<"\n";

}

int SNF_Parser::getSymbolType(char symb)
{
    if (symb=='(') return SYMBOL_LBRACKET;
    if (symb==')') return SYMBOL_RBRACKET;
    if (symb=='&' || symb=='*') return SYMBOL_CONJUNCTION;
    if (symb=='|' || symb=='+') return SYMBOL_DISJUNCTION;
    if (symb=='!' || symb=='-') return SYMBOL_INVERSE;
    if (isdigit(symb) || isalpha(symb)) return SYMBOL_OPERAND;
    if (symb==' ') return SYMBOL_SPACE;
    if (symb=='\0') return SYMBOL_ZERO;

    return SYMBOL_OTHER;
}

//so scary...
void SNF_Parser::getVariables(std::vector<std::string> &variables)
{
    std::string currVar="";

    int lena=0;
    int currType;
    int isDisjunstionPrev=-1, isDisjunctionCurr=-1;

while (getSymbolType(_input[lena++])!=SYMBOL_OPERAND); //if there is a bracket

lena--;

    while (_input[lena]!='\0')
    {
       if(isDisjunctionCurr!=-1) isDisjunstionPrev=isDisjunctionCurr;


        currVar=getOperand(lena);
        if (currVar!="")
          variables.push_back(currVar);

        currType=getSymbolType(_input[lena-1]);


        //conjunction is "*" or ()() or x(.. or ..)x
        if (currType==SYMBOL_CONJUNCTION ||
          (currType==SYMBOL_RBRACKET && getSymbolType(_input[lena])==SYMBOL_LBRACKET)||
           (currType==SYMBOL_RBRACKET && getSymbolType(_input[lena])==SYMBOL_OPERAND))
             isDisjunctionCurr=0;

        //situation like as: x(y+z)
        else if (currType==SYMBOL_LBRACKET && getSymbolType(_input[lena])==SYMBOL_OPERAND)
        {
            int tmp=lena;
            getOperand(tmp);
            if (getSymbolType(_input[tmp-1])==SYMBOL_DISJUNCTION){
                if (isDisjunctionCurr==0 || isDisjunctionCurr==-1) return;
                    else isDisjunctionCurr=1;
            }
            else if (getSymbolType(_input[tmp-1])==SYMBOL_CONJUNCTION){
                if (isDisjunctionCurr==1 || isDisjunctionCurr==-1) return;
                    else isDisjunctionCurr=0;
            }

            else if (isDisjunctionCurr==-1) isDisjunctionCurr=0;
        }

        else if (currType==SYMBOL_DISJUNCTION) isDisjunctionCurr=1;
        else isDisjunctionCurr=-1;

        if(isDisjunctionCurr!=-1 && isDisjunstionPrev!=-1)
             if (isDisjunctionCurr!=isDisjunstionPrev)
                  return;
    }
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

            //like as: (x+y+)z
            if (getSymbolType(_input[i-1])!=SYMBOL_OPERAND &&
                    getSymbolType(_input[i-1])!=SYMBOL_RBRACKET) return false;
            rCount++;
        }
        // y(+x)
        else if (getSymbolType(_input[i])==SYMBOL_LBRACKET)
        {
            if (getSymbolType(_input[i+1])!=SYMBOL_OPERAND &&
                getSymbolType(_input[i+1])!=SYMBOL_INVERSE&&
                getSymbolType(_input[i+1]) !=SYMBOL_LBRACKET)return false;
            lCount++;
        }
    }
    if (lCount==rCount) return true;
    return false;
  }

void SNF_Parser::removeUnused()
 {
     int i=0;
     while (_input[i]!='\0')
     {
         if (getSymbolType(_input[i])==SYMBOL_OTHER)
             _input.erase(i,1);
         else i++;
     }
    i=0;
     while (_input[i]!='\0')
     {
         if (getSymbolType(_input[i])==SYMBOL_SPACE)         
             _input.erase(i,1);             

        else i++;
     }

 }


std::string SNF_Parser::getOperand (int &index)
   {
    std::string output;
    while (getSymbolType(_input[index])!=SYMBOL_CONJUNCTION &&
           getSymbolType(_input[index])!=SYMBOL_DISJUNCTION &&
           getSymbolType(_input[index])!=SYMBOL_LBRACKET &&
           getSymbolType(_input[index])!=SYMBOL_RBRACKET &&
                 getSymbolType(_input[index])!=SYMBOL_ZERO)
    {
        if (getSymbolType(_input[index])==SYMBOL_OPERAND ||
            getSymbolType(_input[index])==SYMBOL_INVERSE) output+=_input[index];
        index++;
    }
    index++;

   return output;
   }
