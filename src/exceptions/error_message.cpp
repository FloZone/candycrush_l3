#include "exceptions/error_message.h"

MessageError::MessageError(const char* file, const char* function, const char* msg)
    : Error(file, function)
{
    std::ostringstream oss;
    oss << "        MESSAGE : " << msg << std::endl;

    this -> msg += oss.str();
}

MessageError::~MessageError() throw()
{

}

const char* MessageError::what() const throw()
{
    return this -> msg.c_str();
}
