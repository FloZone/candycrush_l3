#include "exceptions/error.h"

Error::Error(const char* file, const char* function)
{
    std::ostringstream oss;
    oss << "ERROR : in file '" << file << "', in function '" << function << std::endl;

    this -> msg = oss.str();
}

Error::~Error() throw()
{

}

const char* Error::what() const throw()
{
    return this -> msg.c_str();
}
