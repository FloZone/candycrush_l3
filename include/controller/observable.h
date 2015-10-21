#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "observer.h"

class Observer;

class Observable
{
public:
    virtual ~Observable();

    void addObserver(Observer* _observer);
    void removeObserver();
    virtual void notifyObserver() = 0;
    virtual void update(bool,int, int, int, int) = 0;

protected:
    Observer* observer;
};

#endif // OBSERVABLE_H
