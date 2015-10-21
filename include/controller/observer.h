#ifndef OBSERVER_H
#define OBSERVER_H

#include "observable.h"

class Observable;
class Level;
class Grid;

class Observer
{
public:
    virtual ~Observer();

    void addObservable(Observable* _observable);
    void removeObservable();
    virtual void notifyObservable(int x1, int y1, int x2, int y2) = 0;
    virtual void update(const Level &) = 0;
    virtual void update(const Level &, bool,bool,int,int,int,int) = 0;

protected:
    Observable* observable;
};

#endif // OBSERVER_H
