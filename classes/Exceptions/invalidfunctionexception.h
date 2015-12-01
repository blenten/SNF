#ifndef INVALIDFUNCTIONEXCEPTION_H
#define INVALIDFUNCTIONEXCEPTION_H
#include <string>

class InvalidFunctionException
{
private:
  std::string errorText;

public:
    InvalidFunctionException();
    InvalidFunctionException(std::string error);
    inline std::string getError(){return errorText;}
};

#endif // INVALIDFUNCTIONEXCEPTION_H
