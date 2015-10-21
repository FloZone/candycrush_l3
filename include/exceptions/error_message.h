#ifndef ERROR_MESSAGE_H
#define ERROR_MESSAGE_H

#include "error.h"

class MessageError : public Error
{
public:
    MessageError(const char* file, const char* function, const char* msg);
    virtual ~MessageError() throw();

    virtual const char* what() const throw();
};

#endif // ERROR_MESSAGE_H
