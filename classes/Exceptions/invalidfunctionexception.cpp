#include "invalidfunctionexception.h"

InvalidFunctionException::InvalidFunctionException(std::string error)
{
    errorText=error;
}

InvalidFunctionException::InvalidFunctionException()
{
    errorText="Default";

}
