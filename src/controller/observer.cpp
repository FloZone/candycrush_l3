#include <iostream>

#include "controller/observer.h"

Observer::~Observer()
{
    if(observable)
    {
        observable -> removeObserver();
        observable = NULL;
    }
}

void Observer::addObservable(Observable *_observable)
{
    removeObservable();
    observable = _observable;
}

void Observer::removeObservable()
{
    observable = NULL;
}
