#include <iostream>
#include "models/sweet.h"

Sweet::Sweet(Color _color)
    : color(_color)
{

}

Sweet::~Sweet() {}

Sweet::Color Sweet::getColor()
{
    return color;
}

void Sweet::setColor(Sweet::Color _color)
{
    color = _color;
}
