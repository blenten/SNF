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
    bool invertion;
};
///-----------------///
typedef vector<Variable> Operand;
typedef vector<Operand> Expression;

///----------------///

inline Variable::Variable(string name = "", bool invertion=false)
{
    this->name = name;
    this->invertion = invertion;
}
inline bool Variable::operator==(Variable &var)
{
    if(name==var.name && invertion==var.invertion)  return true;
    return false;
}

#endif // LVAR_H
