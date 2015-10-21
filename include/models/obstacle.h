#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "element.h"

class Obstacle : public Element
{
public:
    enum Type
    {
        WALL
        /*
         * Rajouter ici les nouveaux types d'obstacles
         *
         */
    };

    Obstacle(Type _type = WALL);
    ~Obstacle();

    bool playable();
    bool isBlocking();
    bool hasSweet();

    Type getType();
    void setType(Type _type);
private:
    Type type;
};

#endif // OBSTACLE_H
