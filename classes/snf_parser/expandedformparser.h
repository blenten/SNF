/**
  \file
  */

#ifndef EXPANDEDFORMPARSER_H
#define EXPANDEDFORMPARSER_H

#include "parser.h"

/**
 * @brief OperationState
 *
 * Перечисление состояний текущих операций. Используется при считывании
 */
enum OperationState
{
    UndefinedToDisjunction = -5,
    UndefinedToConjunction = -4,
    ConjunctionToDinsjunction = -3,
    DisjunctionToConjunction = -2,
    Undefined = -1,
    Disjunction = 0,
    Conjunction = 1
};

/**
 * @brief ExpandedFormParser
 *
 * Парсер для развернутой формы ввода функций
 */
class ExpandedFormParser: public Parser
{
private:    
    /**
     * @brief initialChecking
     *
     * Начальная проверка корректности функции перед считыванием переменных
     * @throw InvalidFunctionException
     */
    void initialChecking();

    /**
     * @brief removeUseless
     *
     * Убирает неиспользуемые при записи функций символы из строки
     */
    void removeUseless();

    /**
     * @brief checkBrackets
     *
     * Проверяет правильность взаимного расположения скобок
     * @throw InvalidFunctionException
     */
    void checkBrackets();

    /**
     * @brief insertConjunctionSymbols
     *
     * Заменяет двойные инверсии на конъюнкцию. Вставляет конъюнкцию после операнда перед открывающей скобкой и после закрывающей перед знаком инверсии.
     */
    void insertConjunctionSymbols();

    /**
     * @brief checkInversions
     *
     * Проверяет правильность расстановки инверсий
     *
     * @throw InvalidFunctionException
     */
    void checkInversions();

    /**
     * @brief parseExpandedForm
     *
     * Считывает функцию из строки
     * @throw InvalidFunctionException
     * @return Считанная функция
     */
    FunctionType parseExpandedForm();

    /**
     * @brief getVariables
     *
     * Читает список используемых переменных в функции и возвращает ее тип
     * @return СНДФ или СНКФ
     */
    FunctionType getVariables();

    /**
     * @brief increaseIndexToVariable
     *
     * Увеличивает индекс, пока тот не будет указывать на ближайшую переменную, инверсию или конец входной строки
     * @param index
     * @return Индекс
     */
    size_t increaseIndexToVariable(size_t index);

    /**
     * @brief isVariablesRepeat
     *
     * Проверяет считанные переменные на предмет повтора
     * @return
     */
    bool isVariablesRepeat();

    /**
     * @brief getVariable
     *
     * Считывает переменную, начиная с заданного индекса
     * @param index
     * @return Переменная (если считана)
     */
    std::string getVariable (size_t index);

    /**
     * @brief increaseIndexToSymbolAfterVariable
     *
     * Увеличивает индекс, пока тот не будет указывать на первый символ после переменной
     * @param index
     * @return Индекс
     */
    size_t increaseIndexToSymbolAfterVariable(size_t index);

    /**
     * @brief getNextState
     *
     * Определяет следующее состояние операции
     * @param lena - индекс
     * @param prevState - предыдущее состояние
     * @return Состояние
     */
    OperationState getNextState(size_t lena, OperationState prevState);

    /**
     * @brief getOperationStateAfterLeftBracket
     *
     * Определяет состояние операции после открывающей скобки
     * @param index
     * @param currState - предыдущее состояние
     * @return Состояние
     */
    OperationState getOperationStateAfterLeftBracket(size_t index, OperationState currState);

    /**
     * @brief fillExpression
     *
     * Считывает все переменные
     * @throw InvalidFunctionException
     * @param ft - тип функции
     */
    void fillExpression(const FunctionType &ft);

    /**
     * @brief addOperandToExpression
     *
     * Прибавляет новый операнд в конец вектора-выражения
     */
    void addOperandToExpression();

    /**
     * @brief parseVariable
     *
     * Конвертирует переменную из строкового представления в объект Variable
     * @param currVar - переменная
     * @return Переменная
     */
    Variable parseVariable(std::string &currVar);

public:
    /**
     * @brief parse
     *
     * Производная функции базового класса
     * @param input - входная строка
     * @param output - выходное выражение для последующей обработки
     * @return СНДФ или СНКФ
     */
    FunctionType parse (std::string input, Expression &output);
};

#endif // EXPANDEDFORMPARSER_H
