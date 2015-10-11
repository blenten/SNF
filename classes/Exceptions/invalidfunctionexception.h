#ifndef INVALIDFUNCTIONEXCEPTION_H
#define INVALIDFUNCTIONEXCEPTION_H
#include <string>
#include "snf_lib_global.h"

class SNF_LIBSHARED_EXPORT InvalidFunctionException
{

private:
  std::string errorText;

public:
    InvalidFunctionException();
    InvalidFunctionException(std::string error);
    inline std::string getError(){return errorText;}
};

#endif // INVALIDFUNCTIONEXCEPTION_H
