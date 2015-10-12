#ifndef LVAR_H
#define LVAR_H

#include<string>
#include<vector>

using namespace std;
/// Logiv Variable
class Variable
{
public:
    Variable(string, bool);
    bool operator==(Variable&);
    string name;
    bool inversion;
};
///-----------------///
typedef vector<Variable> Operand;
typedef vector<Operand> Expression;

///----------------///

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
