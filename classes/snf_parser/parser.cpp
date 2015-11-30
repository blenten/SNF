#include "parser.h"

Parser::~Parser()
{
}

//bool Parser::containsAllOperands()
//{
//    removeRepeatingOperands();
//    uint64_t max = pow (2, expression->at(0).variables.size());
//    uint64_t contains = expression->size();
//    if (max==contains) return true;
//    return false;
//}

//void Parser::removeRepeatingOperands()
//{
//    if (expression->size()<=1) return;

//    for(size_t i=0; i<expression->size()-1; i++)
//    {
//        size_t j=i+1;
//        while(j<expression->size())
//        {
//            if(expression->at(i)==expression->at(j))
//            {
//                expression->erase(expression->begin()+j);
//            }else
//            {
//                j++;
//            }
//        }
//    }
//}
