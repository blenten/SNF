/**
  \file
*/

#ifndef INVALIDFUNCTIONEXCEPTION_H
#define INVALIDFUNCTIONEXCEPTION_H
#include <string>

/**
 * @brief InvalidFunctionException
 *
 * Класс-исключение, выбрасываемое в случае некорректного ввода
*/
class InvalidFunctionException
{
private:
  std::string errorText;

public:
     /**
     * @brief InvalidFunctionException
     *
     * Конструктор с текстом ошибки по умолчанию
     */
    InvalidFunctionException();
    /**
     * @brief InvalidFunctionException
     * @param error - текст ошибки
     */
    InvalidFunctionException(std::string error);

    /**
     * @brief getError
     *
     * Возвращает текст ошибки
     * @return Текст ошибки
     */
    inline std::string getError(){return errorText;}
};

#endif // INVALIDFUNCTIONEXCEPTION_H
