#include "snf_parser.h"

FunctionType SNF_Parser::parse(std::string input, Expression &output)
{
   FunctionType ft=OTHER;
    output.clear();
    _input=input;
     removeUnused();
    if (_input.length()==0) return OTHER;
    if (!checkBrackets()) return OTHER;
    if (!checkInversions()) return OTHER;
    std::vector <std::string> variables;
    ft= getVariables(variables);
    if (variables.size()==0) return OTHER;
    for (unsigned int i=0;i<variables.size();i++)

    if (isVariablesRepeat(variables)) return OTHER;

    fillExpressionVector(output, ft, variables);


    return ft;

}

SymbolType SNF_Parser::getSymbolType(char symb)
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
    variables.clear();
    std::string currVar="";
    int lena=0;
    int currType;
   OperationState prevState=Undefined, currState=Undefined;

    while (getSymbolType(_input[lena])!=SYMBOL_OPERAND &&
           getSymbolType(_input[lena])!=SYMBOL_ZERO){lena++;} //if there is a bracket


    while (_input[lena]!='\0')
    {
       if(currState!=Undefined) prevState=currState;

        currVar=getOperand(lena);
        if (currVar!="")
          variables.push_back(currVar);

        currType=getSymbolType(_input[lena-1]);

        //conjunction is "*" or ()() or x(.. or ..)x
        if (currType==SYMBOL_CONJUNCTION ||
          (currType==SYMBOL_RBRACKET && getSymbolType(_input[lena])==SYMBOL_LBRACKET)||
           (currType==SYMBOL_RBRACKET && getSymbolType(_input[lena])==SYMBOL_OPERAND))
            currState=Conjunction;

        else if (currType==SYMBOL_LBRACKET && getSymbolType(_input[lena])==SYMBOL_OPERAND) //situation like as: x(y+z)
        {
           currState=getOperationStateAfterLBracket(lena, currState);
           if (currState==DisjunctionToConjunction||
               currState==ConjunctionToDinsjunction)return prevState? SKNF:SDNF;
           else if (currState==UndefinedToDisjunction) return (prevState)? SDNF:SKNF;
           else if (currState==UndefinedToConjunction){ prevState=Conjunction; currState=Conjunction;}
        }

        else if (currType==SYMBOL_DISJUNCTION) currState=Disjunction;
        else currState=Undefined;

        if(currState!=Undefined && prevState!=Undefined &&
                currState!=DisjunctionToConjunction &&
                currState!=ConjunctionToDinsjunction && currState!=prevState)
           return (prevState)? SKNF:SDNF;

    }

    return (prevState)? SKNF:SDNF;
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
       else if (getSymbolType(_input[index])==SYMBOL_OPERAND)output+=_input[index];

        index++;
    }
    index++;
   return output;
   }

std::string SNF_Parser::getOperandToFill (int &index)
{
     std::string output;
     while (getSymbolType(_input[index])!=SYMBOL_CONJUNCTION &&
            getSymbolType(_input[index])!=SYMBOL_DISJUNCTION &&
            getSymbolType(_input[index])!=SYMBOL_LBRACKET &&
            getSymbolType(_input[index])!=SYMBOL_RBRACKET &&
            getSymbolType(_input[index])!=SYMBOL_ZERO)
     {
        if (getSymbolType(_input[index])==SYMBOL_OPERAND ||
               getSymbolType(_input[index])==SYMBOL_INVERSE)output+=_input[index];

         index++;
     }
     index++;
    return output;
}


OperationState SNF_Parser::getOperationStateAfterLBracket(int index, OperationState currState)
{
       getOperand(index);
       if (getSymbolType(_input[index-1])==SYMBOL_DISJUNCTION){

           if (currState==Conjunction) return ConjunctionToDinsjunction;
           else if (currState==Undefined) return UndefinedToDisjunction;
           else currState=Disjunction;
       }
       else if (getSymbolType(_input[index-1])==SYMBOL_CONJUNCTION){
           if (currState==Disjunction) return DisjunctionToConjunction;
           else if (currState==Undefined) return UndefinedToConjunction;
           else currState=Conjunction;
       }

       else if (currState==Undefined) currState=Conjunction;
       return currState;
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

bool SNF_Parser::checkInversions()
{
 int len=_input.size();
 for (int i=0;i<len-1;i++)
     if (getSymbolType(_input[i])== SYMBOL_INVERSE && getSymbolType(_input[i+1])==SYMBOL_INVERSE)
     {
         _input.erase(i,2);
         _input.insert(i,"&");
         len--;       
     }
    else if (getSymbolType(_input[i])== SYMBOL_INVERSE && getSymbolType(_input[i+1])!=SYMBOL_OPERAND) return 0;

 if (getSymbolType(_input[len-1])==SYMBOL_INVERSE) return 0;
 return 1;

}

void SNF_Parser::fillExpressionVector(Expression& expression, FunctionType& ft,
                                      std::vector<std::string> & variables)
{
    OperationState os=(ft==SKNF)? Disjunction: Conjunction;

    int lena=0, operandIndex=0, varIndex=0;

    while (getSymbolType(_input[lena])!=SYMBOL_OPERAND &&
           getSymbolType(_input[lena])!=SYMBOL_ZERO){lena++;}
    OperationState currState=os;

   addOperandToVector(expression);


    while (_input[lena!='\0'])
    {
        std::string currVar = getOperandToFill(lena);
        Variable var;
        if (getSymbolType(currVar[0])==SYMBOL_INVERSE)
        {
            var.inverted=true;
            currVar.erase(0,1);
        }
        else var.inverted=false;
        var.variable=currVar;

        if (varIndex<variables.size() && currVar == variables[varIndex] && currVar!="")
        {
            expression.at(operandIndex).push_back(var);
            varIndex++;
        }
        else if (currVar!="")
        {
            ft=OTHER;
            return;
        }
        if (_input[lena]=='\0') return;
        currState=getNextState(lena, currState);
        if (currState!=os ||variables[variables.size()-1]==currVar )
        {
            if(varIndex>=variables.size()-1)
            {
                varIndex=0;
                addOperandToVector(expression);
                operandIndex++;
            }
            else if (varIndex)
            {
                ft=OTHER;
                return;
            }
        }

    }

}


OperationState SNF_Parser::getNextState(int & lena, OperationState prevState)
{

    SymbolType currType=getSymbolType(_input[lena-1]);
    OperationState currState;
    if (currType==SYMBOL_CONJUNCTION ||
      (currType==SYMBOL_RBRACKET && getSymbolType(_input[lena])==SYMBOL_LBRACKET)||
       (currType==SYMBOL_RBRACKET && getSymbolType(_input[lena])==SYMBOL_OPERAND))
        return Conjunction;

    else if (currType==SYMBOL_LBRACKET && getSymbolType(_input[lena])==SYMBOL_OPERAND)
    {
       currState=getOperationStateAfterLBracket(lena, currState);
       if (currState==DisjunctionToConjunction) return Conjunction;
          else if( currState==ConjunctionToDinsjunction)return Disjunction;
       else if (currState==UndefinedToDisjunction) return Disjunction;
       else if (currState==UndefinedToConjunction) return Conjunction;
    }

    else if (currType==SYMBOL_DISJUNCTION) return Disjunction;
    else currState = Undefined;

    if(currState!=Undefined && prevState!=Undefined &&
            currState!=DisjunctionToConjunction &&
            currState!=ConjunctionToDinsjunction && currState!=prevState)
       return (prevState==Conjunction)? Disjunction:Conjunction;

}


void SNF_Parser::addOperandToVector (Expression & expression)
{
    Operand op;
    expression.push_back(op);
}
