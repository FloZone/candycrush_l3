#include <iostream>
#include "models/playable.h"

/*
 * Constructeur par défaut ou avec difficulté
 *
 */

Playable::Playable(Difficulty::Name _difficulty)
    : sweet(NULL), difficulty(_difficulty) {}

/*
 * Constructeur de recopie
 *
 */

Playable::Playable(const Playable & _playable)
{
    sweet = new Sweet(*(_playable.sweet));
    difficulty = _playable.difficulty;
}

/*
 * Destructeur
 *
 */

Playable::~Playable()
{
    if(sweet)
    {
        delete sweet;
        sweet = NULL;
    }
}

/*
 * Surcharge de l'opérateur d'affectation
 *
 */

Playable & Playable::operator=(const Playable & _playable)
{
    if(this != &_playable)
    {
        if(sweet)
            delete sweet;

        sweet = new Sweet(*(_playable.sweet));
        difficulty = _playable.difficulty;
    }

    return *this;
}

/*
 * Accesseurs
 *
 */

Sweet* Playable::getSweet()
{
    return sweet;
}

void Playable::setSweet(const Sweet &_sweet)
{
    if(sweet)
        delete sweet;

    sweet = new Sweet(_sweet);
}

void Playable::setSweet(Sweet *_sweet)
{
    sweet = _sweet;
}

Difficulty Playable::getDifficulty()
{
    return difficulty;
}

void Playable::setDifficulty(const Difficulty &_difficulty)
{
    difficulty = _difficulty;
}

/*
 * Implémentatoin de Element
 *
 */

bool Playable::playable()
{
    return true;
}

bool Playable::isBlocking()
{
    return difficulty.isBlocking();
}

bool Playable::hasSweet()
{
    return sweet != NULL;
}

/*
 * Fonctions
 *
 */

void Playable::deleteSweet()
{
    if(sweet)
    {
        delete sweet;
        sweet = NULL;
    }
}
