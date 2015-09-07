#include "expandedformparser.h"

FunctionType ExpandedFormParser::parse(std::string input, Expression &output)
{
     expression=&output;
    _input=input;
    initialChecking();

    return parseExpandedForm();
}

void ExpandedFormParser::initialChecking()
{
    expression->clear();
    variables.clear();
    removeUseless();
    if (_input.length()==0) throw InvalidFunctionException("%NoOperandsAndVariables");
    checkBrackets();
    insertConjunctionSymbols();
    checkInversions();
}

void ExpandedFormParser::removeUseless()
{
    size_t i=0;
    while (getSymbolType(_input[i])!=SYMBOL_ZERO)
    {
        if (getSymbolType(_input[i])==SYMBOL_OTHER || getSymbolType(_input[i])==SYMBOL_SPACE || getSymbolType(_input[i])==SYMBOL_COMMA)
            _input.erase(i,1);
        else i++;
    }
}

void ExpandedFormParser::checkBrackets()
{
     size_t len=_input.length();
     unsigned int lCount=0, rCount=0;

     for (size_t i=0;i<len+1;i++)
     {
         if (getSymbolType(_input[i])==SYMBOL_RBRACKET)
         {
             if (lCount<=rCount) throw InvalidFunctionException("%BracketsNesting@"+std::to_string(i));

             //like as: (x+y+)z
             if (getSymbolType(_input[i-1])!=SYMBOL_OPERAND &&
                     getSymbolType(_input[i-1])!=SYMBOL_RBRACKET)
                 throw InvalidFunctionException ("%OperationBeforeRBracket@"+std::to_string(i));
             rCount++;
         }
         // y(+x)
         else if (getSymbolType(_input[i])==SYMBOL_LBRACKET)
         {
             if (getSymbolType(_input[i+1])!=SYMBOL_OPERAND&&
                 getSymbolType(_input[i+1])!=SYMBOL_INVERSE&&
                 getSymbolType(_input[i+1]) !=SYMBOL_LBRACKET) throw InvalidFunctionException ("%NoOperandAfterLBracket@"+std::to_string(i));
             lCount++;
         }
     }
     if (lCount!=rCount)throw InvalidFunctionException ("%BracketsNumberIsNotEqual");
}

FunctionType ExpandedFormParser::parseExpandedForm()
{
    FunctionType ft=OTHER;
    ft = getVariables();

    if (variables.size()==0) throw InvalidFunctionException("%NoVariables");

    if (isVariablesRepeat()) throw InvalidFunctionException("%RepeatingVariables");

    fillExpression(ft);

    return ft;
}

void ExpandedFormParser::insertConjunctionSymbols()
{
    int len=_input.size();
    for (int i=0;i<len-1;i++)
        if (getSymbolType(_input[i])== SYMBOL_INVERSE && getSymbolType(_input[i+1])==SYMBOL_INVERSE)
        {
            _input.erase(i,2);
            _input.insert(i,"&");
            len--;
        }
        else if (getSymbolType(_input[i])== SYMBOL_OPERAND && getSymbolType(_input[i+1])==SYMBOL_LBRACKET)
        {
             _input.insert(i+1,"&");
             len++;
             i++;
        }
        else if (getSymbolType(_input[i])==SYMBOL_INVERSE && i>0 &&
                (getSymbolType(_input[i-1])==SYMBOL_OPERAND || getSymbolType(_input[i-1])==SYMBOL_RBRACKET ))
        {
             _input.insert(i, "&");
             len++;
             i++;
        }
}

void ExpandedFormParser::checkInversions()
{
    size_t len=_input.size();
    for (size_t i=0;i<len-1;i++)
        if (getSymbolType(_input[i])== SYMBOL_INVERSE && getSymbolType(_input[i+1])!=SYMBOL_OPERAND)
            throw InvalidFunctionException ("%NoOperandAfterInversion@"+ std::to_string(i));

    if (getSymbolType(_input[len-1])==SYMBOL_INVERSE) throw InvalidFunctionException("%LastSymbolIsInversion");

}

FunctionType ExpandedFormParser::getVariables()
{
     variables.clear();
     std::string currVar="";
     size_t lena=0;
     OperationState prevState=Undefined, currState=Undefined;

     lena = increaseIndexToVariable(lena);

     while (getSymbolType(_input[lena])!=SYMBOL_ZERO)
     {
        if(currState!=Undefined) prevState=currState;

         currVar=getOperand(lena);
         if (getSymbolType(_input[lena])!=SYMBOL_ZERO) lena++;

         if (getSymbolType(currVar[0])==SYMBOL_INVERSE) currVar.erase(0,1);

         if (currVar!="")
           variables.push_back(currVar);

         currState=getNextState(lena,currState);
         if (currState!=Undefined && prevState!= Undefined && currState!=prevState)
             return (currState==Conjunction? SNKF:SNDF);
     }
     return (prevState==Disjunction? SNKF:SNDF);
     return OTHER;
}

size_t ExpandedFormParser::increaseIndexToVariable(size_t index)
{
    while (getSymbolType(_input[index])!=SYMBOL_OPERAND &&
           getSymbolType(_input[index])!=SYMBOL_ZERO &&
           getSymbolType(_input[index])!=SYMBOL_INVERSE){index++;}
    return index;
}

std::string ExpandedFormParser::getOperand (size_t &index)
{
     std::string output;
     while (getSymbolType(_input[index])!=SYMBOL_CONJUNCTION &&
            getSymbolType(_input[index])!=SYMBOL_DISJUNCTION &&
            getSymbolType(_input[index])!=SYMBOL_LBRACKET &&
            getSymbolType(_input[index])!=SYMBOL_RBRACKET &&
            getSymbolType(_input[index])!=SYMBOL_ZERO &&
            (getSymbolType(_input[index])==SYMBOL_OPERAND ||
             getSymbolType(_input[index])==SYMBOL_INVERSE))
     {
            output+=_input[index];
            index++;
     }
    return output;
}

OperationState ExpandedFormParser::getNextState(size_t & lena, OperationState prevState)
{
    SymbolType currType=getSymbolType(_input[lena-1]);
    OperationState currState=Undefined;

    if (currType==SYMBOL_CONJUNCTION ||
      (currType==SYMBOL_RBRACKET && getSymbolType(_input[lena])==SYMBOL_LBRACKET)||
       (currType==SYMBOL_RBRACKET && getSymbolType(_input[lena])==SYMBOL_OPERAND))
        return Conjunction;

    else if (currType==SYMBOL_RBRACKET && getSymbolType(_input[lena])==SYMBOL_DISJUNCTION)
        return Disjunction;

    else if (currType==SYMBOL_DISJUNCTION) return Disjunction;

    else if (currType==SYMBOL_LBRACKET && getSymbolType(_input[lena])==SYMBOL_OPERAND)
    {
       currState=getOperationStateAfterLBracket(lena, prevState);

       if (currState==DisjunctionToConjunction) return Conjunction;
       else if(currState==ConjunctionToDinsjunction)return Disjunction;
       else if (currState==UndefinedToDisjunction) return Disjunction;
       else if (currState==UndefinedToConjunction) return Conjunction;
    }

    else currState = Undefined;

    if(currState!=Undefined && prevState!=Undefined &&
            currState!=DisjunctionToConjunction &&
            currState!=ConjunctionToDinsjunction && currState!=prevState)
       return (prevState==Conjunction)? Disjunction:Conjunction;

    return Undefined;
}

OperationState ExpandedFormParser::getOperationStateAfterLBracket(size_t index, OperationState currState)
{
    getOperand(index);
    if (getSymbolType(_input[index])!=SYMBOL_ZERO) index++;

    if (getSymbolType(_input[index-1])==SYMBOL_DISJUNCTION)
    {
        if (currState==Conjunction) return ConjunctionToDinsjunction;
        else if (currState==Undefined) return UndefinedToDisjunction;
        else return Disjunction;
    }
    else if (getSymbolType(_input[index-1])==SYMBOL_CONJUNCTION)
    {
        if (currState==Disjunction) return DisjunctionToConjunction;
        else if (currState==Undefined) return UndefinedToConjunction;
        else return Conjunction;
    }

    else if (currState==Undefined) return Conjunction;
    return currState;
}

bool ExpandedFormParser::isVariablesRepeat()
{
    size_t len=variables.size();
    if (len==1) return 0;

    for (size_t i=0;i<len-1;i++)
        for (size_t j=i+1;j<len;j++)
            if (variables[i]==variables[j]) return 1;

    return 0;
}

void ExpandedFormParser::fillExpression(const FunctionType& ft)
{
    OperationState os=(ft==SNKF)? Disjunction: Conjunction;
    OperationState currState=os;

    size_t lena=0, operandIndex=0, varIndex=0;
    size_t variablesNumber=variables.size();

    addOperandToExpression();

    while (getSymbolType(_input[lena])!=SYMBOL_ZERO)
    {
        std::string currVar = getOperand(lena);
        lena = increaseIndexToVariable(lena);

        Variable var = parseVariable(currVar);

        if (varIndex<variablesNumber && currVar!="" && currVar == variables[varIndex])
        {
            expression->at(operandIndex).push_back(var);
            varIndex++;
        }
        else if (currVar!="")
           throw InvalidFunctionException ("%SequenceOfVariablesIsBroken@"+std::to_string(lena));

        if (getSymbolType(_input[lena])==SYMBOL_ZERO)
        {
           if (varIndex<variablesNumber)throw InvalidFunctionException("%IncorrectOperationChanging@"+std::to_string(lena));
            return;
        }

        currState=getNextState(lena, currState);
        if (currState!=os && variables[variablesNumber-1]==currVar)
        {
            if(varIndex>=variablesNumber-1)
            {
                varIndex=0;
                addOperandToExpression();
                operandIndex++;
            }
            else if (varIndex)
               throw InvalidFunctionException ("%SequenceOfVariablesIsBroken@"+std::to_string(lena));
        }
        else if (currState!=os && currState!=Undefined && currVar!="")throw InvalidFunctionException("%IncorrectOperationChanging@"+std::to_string(lena));
    }
}

void ExpandedFormParser::addOperandToExpression ()
{
    Operand op;
    expression->push_back(op);
}

Variable ExpandedFormParser::parseVariable(std::string &currVar)
{
    Variable var;
    if (getSymbolType(currVar[0])==SYMBOL_INVERSE)
    {
        var.invertion=true;
        currVar.erase(0,1);
    }
    var.name=currVar;

    return var;
}
