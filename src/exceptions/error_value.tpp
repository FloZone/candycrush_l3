#include "exceptions/error_value.h"

template <class T>
ValueError<T>::ValueError(const char* file, const char* function, const char* msg, const T &value)
    : MessageError(file, function, msg)
{
    std::ostringstream oss;
    oss << "--- THROWN VALUE ----------------------------------------" << std::endl
        << value << std::endl
        << "---------------------------------------------------------" << std::endl;

    this -> msg += oss.str();
}

template <class T>
ValueError<T>::~ValueError() throw()
{

}

template <class T>
const char* ValueError<T>::what() const throw()
{
    return this -> msg.c_str();
}


/*
 * Spécialisation pour les int
 *
 */
template <>
ValueError<int>::ValueError(const char* file, const char* function, const char* msg, const int &value)
    : MessageError(file, function, msg)
{
    std::ostringstream oss;
    oss << "        THROWN VALUE : " << value << std::endl;

    this -> msg += oss.str();
}

template <>
ValueError<int>::~ValueError() throw()
{

}

template <>
const char* ValueError<int>::what() const throw()
{
    return this -> msg.c_str();
}
