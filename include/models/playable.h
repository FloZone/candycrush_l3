#ifndef PLAYABLE_H
#define PLAYABLE_H

#include "element.h"
#include "sweet.h"
#include "difficulty.h"

class Playable : public Element
{
public:
    Playable(Difficulty::Name _difficulty = Difficulty::NONE);
    Playable(const Playable &_playable);
    ~Playable();
    Playable & operator=(const Playable &);

    bool playable();
    bool isBlocking();
    bool hasSweet();

    Sweet* getSweet();
    void setSweet(const Sweet &_sweet);
    void setSweet(Sweet *_sweet);
    void deleteSweet();

    Difficulty getDifficulty();
    void setDifficulty(const Difficulty &_difficulty);

private:
    Sweet* sweet;
    Difficulty difficulty;
};

#endif // PLAYABLE_H
