#ifndef ELEMENT_H
#define ELEMENT_H

class Element
{
public:
    virtual ~Element();
    virtual bool playable() = 0;
    virtual bool isBlocking() = 0;
    virtual bool hasSweet() = 0;
};

#endif // ELEMENT_H
