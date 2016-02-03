/**
  \file
*/

#ifndef SNF_MINIMIZER_H
#define SNF_MINIMIZER_H

#include "../../classes/snf_parser/snf_parserfacade.h"
#include <sstream>

using namespace std;

/**
 * @brief The INOP_type enum
 */
enum INOP_type
{
    IN=1, invIN=0, NIN=-1
};

/**
 * @brief MINIMIZER
 */
class SNF_Minimizer
{
public:
    /**
     * @brief SNF_Minimizer
     */
    SNF_Minimizer();

    /**
     * @brief parse
     * @param input
     * @return
     */
    bool parse(string input);

    /**
     * @brief match
     */
    void match();

    /**
     * @brief delUnness
     */
    void delUnness();

    /**
     * @brief res_toString
     * @return
     */
    string res_toString();

    /**
     * @brief getLog
     * @return
     */
    string getLog();

    /**
     * @brief minimize
     * @return
     */
    string minimize(string); //for tester only. needs fixing!

private:
    /**
     * @brief checkNecessity
     * @param index
     * @return
     */
    bool checkNecessity(int index);

    /**
     * @brief sortres
     * @param left
     * @param right
     * @param res
     */
    void sortres(int left, int right, Expression& res);

    /**
     * @brief inop
     * @return
     */
    INOP_type inop(Variable&, Operand&);

    /**
     * @brief resolves
     * @param exp
     * @return
     */
    bool resolves(Expression& exp);

    /**
     * @brief matchOperands
     * @param op1
     * @param op2
     * @param result
     * @return
     */
    bool matchOperands(Operand& op1, Operand& op2, Expression& result);

    /**
     * @brief containsAllOperands
     * @return
     */
    bool containsAllOperands();

    /**
     * @brief delsame
     * @param expression
     */
    void delsame(Expression& expression);

    /**
     * @brief log
     */
    void log(Expression&);         //creating log for "steps"
    /**
     * @brief logResult
     */
    void logResult();
    /**
     * @brief logs
     */
    stringstream logs;

    SNF_ParserFacade parser; ///<olerapx
    Expression exp; ///<
    FunctionType expType; ///<
};

#endif // SNF_MINIMIZER_H
