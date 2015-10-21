#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <sstream>
#include <exception>

class Error : public std::exception
{
public:
    Error(const char* file, const char* function);
    virtual ~Error() throw();

    virtual const char* what() const throw();
protected:
    std::string msg;
};

#endif // ERROR_H
