#include <iostream>

#include "controller/observable.h"

Observable::~Observable()
{
    if(observer)
    {
        observer -> removeObservable();
        observer = NULL;
    }
}

void Observable::addObserver(Observer *_observer)
{
    removeObserver();
    observer = _observer;
}

void Observable::removeObserver()
{
    observer = NULL;
}
