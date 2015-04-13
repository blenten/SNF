#include "snf_parser.h"

FunctionType SNF_Parser::parse(std::string input, Expression &output)
{
    FunctionType ft;
    if (input.length()==0) return OTHER;
     _input=input;
     removeUnused();
   if (!checkBrackets()) return OTHER;
   if (!checkOperationAfterInverse()) return OTHER;
   std::vector <std::string> variables;
   ft= getVariables(variables);
  //  for (int i=0;i<variables.size();i++) std::cout<< variables[i]<<" ";
    if (isVariablesRepeat(variables)) return OTHER;

    switch(ft)
    {
    case -1: std::cout <<"OTHER\n"; break;
    case 0: std::cout <<"SDNF\n"; break;
    case 1: std::cout << "SKNF\n"; break;
    }

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


FunctionType SNF_Parser::getVariables(std::vector<std::string> &variables)
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

        else if (currType==SYMBOL_LBRACKET && getSymbolType(_input[lena])==SYMBOL_OPERAND) //situation like as: x(y+z)
        {
           isDisjunctionCurr=checkOperandAfterLBracket(lena, isDisjunctionCurr);
           if (isDisjunctionCurr==-1) return isDisjunstionPrev? SKNF:SDNF;
           else if (isDisjunctionCurr==-2) return isDisjunstionPrev? SDNF:SKNF;
        }

        else if (currType==SYMBOL_DISJUNCTION) isDisjunctionCurr=1;
        else isDisjunctionCurr=-1;

        if(isDisjunctionCurr!=-1 && isDisjunstionPrev!=-1 /*&& isDisjunctionCurr!=isDisjunstionPrev*/)
             return isDisjunstionPrev? SKNF:SDNF;

    }
    return isDisjunstionPrev? SKNF:SDNF;

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
         if (getSymbolType(_input[index])==SYMBOL_INVERSE && index>0 &&
                 (getSymbolType(_input[index-1])==SYMBOL_OPERAND ||getSymbolType(_input[index-1])==SYMBOL_RBRACKET ))
         {
              _input.insert(index, "&");
              index+=1;
              return output;
         }
       else if (getSymbolType(_input[index])==SYMBOL_OPERAND) output+=_input[index];
        index++;
    }
    index++;
   return output;
   }

int SNF_Parser::checkOperandAfterLBracket(int index, int isDisjunctionCurr)
{
       getOperand(index);
       if (getSymbolType(_input[index-1])==SYMBOL_DISJUNCTION){

           if (isDisjunctionCurr==0) return -1;
         else if (isDisjunctionCurr==-1) return -2;
               else isDisjunctionCurr=1;
       }
       else if (getSymbolType(_input[index-1])==SYMBOL_CONJUNCTION){
           if (isDisjunctionCurr==1) return -1;
           else if (isDisjunctionCurr==-1) return -2;
               else isDisjunctionCurr=0;
       }

       else if (isDisjunctionCurr==-1) isDisjunctionCurr=0;

       return isDisjunctionCurr;
}

bool SNF_Parser::isVariablesRepeat(std::vector<std::string> &variables)
 {

    int len=variables.size();
    if (len==1) return 0;

    for (int i=0;i<len-1;i++)
        for (int j=i+1;j<len;j++)
            if (variables[i]==variables[j]) return 1;

    return 0;
 }

bool SNF_Parser::checkOperationAfterInverse()
{
 int len=_input.size();
 for (int i=0;i<len-1;i++)
     if (getSymbolType(_input[i])== SYMBOL_INVERSE && getSymbolType(_input[i+1])!=SYMBOL_OPERAND) return 0;

 if (getSymbolType(_input[len-1])==SYMBOL_INVERSE) return 0;
 return 1;

}
