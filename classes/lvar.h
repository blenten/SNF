/**
  \file
  */

#ifndef LVAR_H
#define LVAR_H

#include<string>
#include<vector>

using namespace std;
/**
 * @brief The Variable class
 *
 * Логическая переменная
 */
class Variable
{
public:
    /**
     * @brief Variable
     *
     * Конструктор
     * @param name - имя переменной
     * @param inversion - инверсия
     */
    Variable(string, bool);
    /**
     * @brief operator ==
     *
     * Перегруженный оператор сравнения
     * @return
     */
    bool operator==(Variable&);
    string name; ///<имя переменной
    bool inversion; ///<инверсия
};

inline Variable::Variable(string name = "", bool inversion=false)
{
    this->name = name;
    this->inversion = inversion;
}
inline bool Variable::operator==(Variable &var)
{
    if(name==var.name && inversion==var.inversion)  return true;
    return false;
}

#endif // LVAR_H
