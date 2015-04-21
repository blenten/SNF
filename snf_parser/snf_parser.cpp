#include "snf_parser.h"

FunctionType SNF_Parser::parse(std::string input, Expression &output)
{
       FunctionType ft=OTHER;
        output.clear();
        _input=input;
         removeUnused();
        if (_input.length()==0) throw InvalidFunctionException("Input string doesn't contain any variables or operands");
        checkBrackets();
        insertConjunctionSymbols();
        checkInversions();
        std::cout <<_input<<"\n";
        std::vector <std::string> variables;
        ft= getVariables(variables);
        if (variables.size()==0) throw InvalidFunctionException("Input string has no variables");

        if (isVariablesRepeat(variables)) throw InvalidFunctionException("Input string has repeating variables");

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
    SymbolType currType;
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
        currState=getNextState(lena,currState);
        if (currState!=Undefined && prevState!= Undefined && currState!=prevState)
            return (currState==Conjunction? SNKF:SNDF);

    }
  return (prevState==Disjunction? SNKF:SNDF);
  return OTHER;
}


void SNF_Parser::checkBrackets()
  {

        int len=_input.length();
        int lCount=0, rCount=0;
        for (int i=0;i<len+1;i++)
        {
            if (getSymbolType(_input[i])==SYMBOL_RBRACKET)
            {
                if (lCount<=rCount) throw InvalidFunctionException("Brackets nesting is violated");

                //like as: (x+y+)z
                if (getSymbolType(_input[i-1])!=SYMBOL_OPERAND &&
                        getSymbolType(_input[i-1])!=SYMBOL_RBRACKET)
                    throw InvalidFunctionException ("Operation before right bracket at position "+toString(i));
                rCount++;
            }
            // y(+x)
            else if (getSymbolType(_input[i])==SYMBOL_LBRACKET)
            {
                if (getSymbolType(_input[i+1])!=SYMBOL_OPERAND&&
                    getSymbolType(_input[i+1])!=SYMBOL_INVERSE&&
                    getSymbolType(_input[i+1]) !=SYMBOL_LBRACKET) throw InvalidFunctionException ("No operand after left bracket");
                lCount++;
            }
        }
        if (lCount!=rCount)throw InvalidFunctionException ("Left brackets number is not equal that right brackets number");

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

void SNF_Parser::checkInversions()
{
 int len=_input.size();
 for (int i=0;i<len-1;i++)   
     if (getSymbolType(_input[i])== SYMBOL_INVERSE && getSymbolType(_input[i+1])!=SYMBOL_OPERAND)
         throw InvalidFunctionException ("No operand after inversion at position "+ toString(i));

 if (getSymbolType(_input[len-1])==SYMBOL_INVERSE) throw InvalidFunctionException("Last symbol in string is inversion");

}

void SNF_Parser::insertConjunctionSymbols()
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

   }



void SNF_Parser::fillExpressionVector(Expression& expression, const FunctionType& ft,
                                      std::vector<std::string> & variables)
{

    OperationState os=(ft==SNKF)? Disjunction: Conjunction;

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
            var.invertion=true;
            currVar.erase(0,1);
        }
        else var.invertion=false;
        var.name=currVar;

        if (varIndex<variables.size() && currVar == variables[varIndex] && currVar!="")
        {
            expression.at(operandIndex).push_back(var);
            varIndex++;
        }
        else if (currVar!="")
           throw InvalidFunctionException ("The sequence of variables is broken");

        if (_input[lena]=='\0')
        {
           if (varIndex<variables.size()) throw InvalidFunctionException("Can't read all variables because of incorrect operation changing");
            return;
        }


        currState=getNextState(lena, currState);
        if (currState!=os  && variables[variables.size()-1]==currVar )
        {
            if(varIndex>=variables.size()-1)
            {
                varIndex=0;
                addOperandToVector(expression);
                operandIndex++;
            }
            else if (varIndex)
               throw InvalidFunctionException ("The sequence of variables is broken");

        }

    }

}


OperationState SNF_Parser::getNextState(int & lena, OperationState prevState)
{
    SymbolType currType=getSymbolType(_input[lena-1]);
    OperationState currState=Undefined;
    if (currType==SYMBOL_CONJUNCTION ||
      (currType==SYMBOL_RBRACKET && getSymbolType(_input[lena])==SYMBOL_LBRACKET)||
       (currType==SYMBOL_RBRACKET && getSymbolType(_input[lena])==SYMBOL_OPERAND))
        return Conjunction;

    else if (currType==SYMBOL_LBRACKET && getSymbolType(_input[lena])==SYMBOL_OPERAND)
    {
       currState=getOperationStateAfterLBracket(lena, prevState);
       if (currState==DisjunctionToConjunction) return Conjunction;
          else if( currState==ConjunctionToDinsjunction)return Disjunction;
       else if (currState==UndefinedToDisjunction) return Disjunction;
       else if (currState==UndefinedToConjunction) return Conjunction;
    }
    else if (currType==SYMBOL_RBRACKET && getSymbolType(_input[lena])==SYMBOL_DISJUNCTION)
        return Disjunction;

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
