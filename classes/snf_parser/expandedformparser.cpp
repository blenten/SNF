#include "expandedformparser.h"

FunctionType ExpandedFormParser::parse(std::string input, Expression &output)
{
     expression = &output;
    _input = input;
    initialChecking();

    return parseExpandedForm();
}

void ExpandedFormParser::initialChecking()
{
    expression->clear();
    variables.clear();
    removeUseless();
    if (_input.length() == 0) throw InvalidFunctionException("%NoOperandsAndVariables");
    checkBrackets();
    insertConjunctionSymbols();
    checkInversions();
}

void ExpandedFormParser::removeUseless()
{
    size_t i = 0;
    while (getSymbolType(_input[i]) != SYMBOL_ZERO)
    {
        if (getSymbolType(_input[i])==SYMBOL_OTHER || getSymbolType(_input[i])==SYMBOL_SPACE || getSymbolType(_input[i])==SYMBOL_COMMA)
            _input.erase(i,1);
        else i++;
    }
}

void ExpandedFormParser::checkBrackets()
{
     size_t len = _input.length();
     unsigned int lCount = 0, rCount = 0;

     for (size_t i=0; i<len+1; i++)
     {
         if (getSymbolType(_input[i])==SYMBOL_RBRACKET)
         {
             if (lCount <= rCount) throw InvalidFunctionException("%BracketsNesting@"+std::to_string(i));

             //like as: (x+y+)z
             if (getSymbolType(_input[i-1]) != SYMBOL_OPERAND &&
                     getSymbolType(_input[i-1]) != SYMBOL_RBRACKET)
                 throw InvalidFunctionException ("%OperationBeforeRBracket@"+std::to_string(i));
             rCount++;
         }
         // y(+x)
         else if (getSymbolType(_input[i]) == SYMBOL_LBRACKET)
         {
             if (getSymbolType(_input[i+1]) != SYMBOL_OPERAND &&
                 getSymbolType(_input[i+1]) != SYMBOL_INVERSE &&
                 getSymbolType(_input[i+1]) != SYMBOL_LBRACKET) throw InvalidFunctionException ("%NoOperandAfterLBracket@"+std::to_string(i));
             lCount++;
         }
     }
     if (lCount!=rCount) throw InvalidFunctionException ("%BracketsNumberIsNotEqual");
}

FunctionType ExpandedFormParser::parseExpandedForm()
{
    FunctionType ft = OTHER;
    ft = getVariables();

    if (variables.size() == 0) throw InvalidFunctionException("%NoVariables");

    if (isVariablesRepeat()) throw InvalidFunctionException("%RepeatingVariables");

    fillExpression(ft);

    return ft;
}

void ExpandedFormParser::insertConjunctionSymbols()
{
    int len = _input.size();
    for (int i=0; i<len-1; i++)
        if (getSymbolType(_input[i]) == SYMBOL_INVERSE && getSymbolType(_input[i+1]) == SYMBOL_INVERSE)
        {
            _input.erase(i,2);
            _input.insert(i,"&");
            len--;
        }
        else if (getSymbolType(_input[i]) == SYMBOL_OPERAND && getSymbolType(_input[i+1]) == SYMBOL_LBRACKET)
        {
             _input.insert(i+1,"&");
             len++;
             i++;
        }
        else if (getSymbolType(_input[i]) == SYMBOL_INVERSE && i > 0 &&
                (getSymbolType(_input[i-1]) == SYMBOL_OPERAND || getSymbolType(_input[i-1]) == SYMBOL_RBRACKET ))
        {
             _input.insert(i, "&");
             len++;
             i++;
        }
}

void ExpandedFormParser::checkInversions()
{
    size_t len = _input.size();
    for (size_t i=0; i<len-1; i++)
        if (getSymbolType(_input[i]) == SYMBOL_INVERSE && getSymbolType(_input[i+1]) != SYMBOL_OPERAND)
            throw InvalidFunctionException ("%NoOperandAfterInversion@" + std::to_string(i));

    if (getSymbolType(_input[len-1]) == SYMBOL_INVERSE) throw InvalidFunctionException("%LastSymbolIsInversion");

}

FunctionType ExpandedFormParser::getVariables()
{
     variables.clear();
     std::string currVar = "";
     size_t lena = 0;
     OperationState currState = Undefined, prevState=Undefined;

     lena = increaseIndexToVariable(lena);

     while (getSymbolType(_input[lena]) != SYMBOL_ZERO)
     {
         currVar = getVariable(lena);
         lena = increaseIndexToSymbolAfterVariable(lena);

         if (getSymbolType(_input[lena]) != SYMBOL_ZERO) lena++;

         if (getSymbolType(currVar[0]) == SYMBOL_INVERSE) currVar.erase(0,1);

         if (variables.size()==0 || currVar != variables[0])
         {
             if (currVar != "")
               variables.push_back(currVar);

             if (getSymbolType(_input[lena]) == SYMBOL_ZERO)
                 return ((currState)==Conjunction? SNDF: SNKF);
         }
         else
             return ((currState)==Conjunction? SNKF: SNDF);


         OperationState nextState = getNextState(lena,currState);
         if (currVar==""&& currState!=Undefined && prevState!=Undefined)
         {
             if (prevState==currState)
                 return ((currState)==Conjunction? SNDF: SNKF);
             else
                 return ((currState)==Conjunction? SNKF: SNDF);
         }

         if (nextState!=Undefined)
         {
             prevState = currState;
             currState = nextState;
         }
     }
     return OTHER;
}

size_t ExpandedFormParser::increaseIndexToVariable(size_t index)
{
    while (getSymbolType(_input[index]) != SYMBOL_OPERAND &&
           getSymbolType(_input[index]) != SYMBOL_ZERO &&
           getSymbolType(_input[index]) != SYMBOL_INVERSE) {index++;}
    return index;
}

std::string ExpandedFormParser::getVariable(size_t index)
{
     std::string output;
     while (getSymbolType(_input[index]) == SYMBOL_OPERAND ||
             getSymbolType(_input[index]) == SYMBOL_INVERSE)
     {
            output += _input[index];
            index++;
     }
    return output;
}

size_t ExpandedFormParser::increaseIndexToSymbolAfterVariable(size_t index)
{
    while (getSymbolType(_input[index]) == SYMBOL_OPERAND ||
            getSymbolType(_input[index]) == SYMBOL_INVERSE)
    {
           index++;
    }
   return index;
}

OperationState ExpandedFormParser::getNextState(size_t lena, OperationState prevState)
{
    SymbolType currType = getSymbolType(_input[lena-1]);
    OperationState currState = Undefined;

    if (currType == SYMBOL_CONJUNCTION ||
      (currType == SYMBOL_RBRACKET && getSymbolType(_input[lena]) == SYMBOL_LBRACKET)||
       (currType == SYMBOL_RBRACKET && getSymbolType(_input[lena]) == SYMBOL_OPERAND))
        return Conjunction;

    if (currType == SYMBOL_RBRACKET && getSymbolType(_input[lena]) == SYMBOL_DISJUNCTION)
        return Disjunction;

    if (currType==SYMBOL_DISJUNCTION) return Disjunction;

    if (currType == SYMBOL_LBRACKET && getSymbolType(_input[lena]) == SYMBOL_OPERAND)
    {
       currState = getOperationStateAfterLeftBracket(lena, prevState);

       if (currState == DisjunctionToConjunction) return Conjunction;
       if (currState == ConjunctionToDinsjunction) return Disjunction;
       if (currState == UndefinedToDisjunction) return Disjunction;
       if (currState == UndefinedToConjunction) return Conjunction;
    }

    return Undefined;
}

OperationState ExpandedFormParser::getOperationStateAfterLeftBracket(size_t index, OperationState currState)
{
    index = increaseIndexToSymbolAfterVariable(index);

    if (getSymbolType(_input[index]) == SYMBOL_DISJUNCTION)
    {
        if (currState == Conjunction) return ConjunctionToDinsjunction;
        else if (currState == Undefined) return UndefinedToDisjunction;
        else return Disjunction;
    }
    if (getSymbolType(_input[index]) == SYMBOL_CONJUNCTION)
    {
        if (currState == Disjunction) return DisjunctionToConjunction;
        else if (currState == Undefined) return UndefinedToConjunction;
        else return Conjunction;
    }

    if (currState == Undefined) return Conjunction;
    return currState;
}

bool ExpandedFormParser::isVariablesRepeat()
{
    size_t len = variables.size();
    if (len == 1) return 0;

    for (size_t i=0; i<len-1; i++)
        for (size_t j=i+1; j<len; j++)
            if (variables[i] == variables[j]) return 1;

    return 0;
}

void ExpandedFormParser::fillExpression(const FunctionType& ft)
{
    OperationState startState = (ft == SNKF) ? Disjunction: Conjunction;
    OperationState currState = startState;

    size_t lena = 0, varIndex = 0;
    size_t variablesNumber = variables.size(), operandsNumber=0;

    while (true)
    {
        std::string currVar = getVariable(lena);
        Variable var = parseVariable(currVar);

        if (currVar==variables[0])
        {
            if (currState==startState && variables.size()>1 && operandsNumber!=0)
                throw InvalidFunctionException("%IncorrectOperationChanging@" + std::to_string(lena));


            varIndex = 0;
            addOperandToExpression();
            operandsNumber++;
        }

        if (varIndex < variablesNumber && currVar != "" && currVar == variables[varIndex])
        {
            if (currState!=startState && currState!=Undefined && variables.size()>1 && varIndex>0)
                throw InvalidFunctionException("%IncorrectOperationChanging@" + std::to_string(lena));


            expression->at(operandsNumber-1).variables.push_back(var);
            varIndex++;
        }
        else if (currVar != "")
           throw InvalidFunctionException ("%SequenceOfVariablesIsBroken@" + std::to_string(lena));

        lena = increaseIndexToSymbolAfterVariable(lena);
        lena = increaseIndexToVariable(lena);

        if (getSymbolType(_input[lena]) == SYMBOL_ZERO)
        {
            if (varIndex < variablesNumber) throw InvalidFunctionException("%UnexpectedEndOfFunction");
            return;
        }
        currState = getNextState(lena, currState);
    }
}

void ExpandedFormParser::addOperandToExpression()
{
    Operand op;
    expression->push_back(op);
}

Variable ExpandedFormParser::parseVariable(std::string &currVar)
{
    Variable var;
    if (getSymbolType(currVar[0]) == SYMBOL_INVERSE)
    {
        var.inversion=true;
        currVar.erase(0,1);
    }
    var.name=currVar;

    return var;
}
