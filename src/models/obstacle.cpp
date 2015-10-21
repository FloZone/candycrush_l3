#include <iostream>
#include "models/obstacle.h"

Obstacle::~Obstacle() {}

Obstacle::Obstacle(Type _type)
    : type(_type) {}

bool Obstacle::playable()
{
    return false;
}

bool Obstacle::isBlocking()
{
    return true;
}

bool Obstacle::hasSweet()
{
    return false;
}

Obstacle::Type Obstacle::getType()
{
    return type;
}

void Obstacle::setType(Type _type)
{
    type = _type;
}
