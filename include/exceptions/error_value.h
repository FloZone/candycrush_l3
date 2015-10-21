#ifndef ERROR_VALUE_H
#define ERROR_VALUE_H

#include <iostream>

#include "error_message.h"

template <class T>
class ValueError : public MessageError
{
public:
    ValueError(const char* file, const char* function, const char* msg, const T &value);
    ~ValueError() throw();

    const char* what() const throw();
};

template class ValueError<int>;

#include "../src/exceptions/error_value.tpp"

#endif // ERROR_VALUE_H
