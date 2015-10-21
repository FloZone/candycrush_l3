#include "models/difficulty.h"

Difficulty::Difficulty(Name _name)
    : name(_name)
{
    switch (_name)
    {
    case Difficulty::NONE :
        blocking = false;
        sweetPresence = true;
        changingWithAdjacent = false;
        break;
    case Difficulty::GEL_1 :
        blocking = false;
        sweetPresence = true;
        changingWithAdjacent = false;
        break;
    case Difficulty::GEL_2 :
        blocking = false;
        sweetPresence = true;
        changingWithAdjacent = false;
        break;
    case Difficulty::CHANTILLY :
        blocking = true;
        sweetPresence = false;
        changingWithAdjacent = true;
        break;
    case Difficulty::CAGE :
        blocking = true;
        sweetPresence = true;
        changingWithAdjacent = false;
        break;
    /* Rajouter ici les nouvelles difficultés
     * ATTENTION : Veiller à rajouter la difficulté dans l'énum
     */
    default:
        throw ValueError<int>("difficulty.cpp"
                    , "Constructor Difficulty::Difficulty(Name)"
                    , "Invalid difficulty value"
                    , _name);
        break;
    }
}

/*
 * Accesseurs
 *
 */

Difficulty::Name Difficulty::getName()
{
    return name;
}

bool Difficulty::isBlocking()
{
    return blocking;
}

bool Difficulty::isSweetPresence()
{
    return sweetPresence;
}

bool Difficulty::isChangingWithAdjacent()
{
    return changingWithAdjacent;
}

void Difficulty::setName(Name _name)
{
    name = _name;
}

void Difficulty::setBlocking(bool _blocking)
{
    blocking = _blocking;
}

void Difficulty::setSweetPresence(bool _sweetPresence)
{
    sweetPresence = _sweetPresence;
}

void Difficulty::setChangingWithAdjacent(bool _changingWithAdjacent)
{
    changingWithAdjacent = _changingWithAdjacent;
}

/*
 * Fonctions
 *
 */
//----------------------Inutilisée (non fonctionelle)------------------------------//
Difficulty Difficulty::change()
{
    Difficulty d;
    switch (name)
    {
    case Difficulty::NONE :
        /* NE RIEN FAIRE */
        break;
    case Difficulty::GEL_1 :
        d.setName(Difficulty::NONE); //name = Difficulty::NONE;
        d.setBlocking(false);
        d.setSweetPresence(true);
        d.setChangingWithAdjacent(false);
        break;
    case Difficulty::GEL_2 :
        d.setName(Difficulty::GEL_1); //name = Difficulty::GEL_1;
        d.setBlocking(false);
        d.setSweetPresence(true);
        d.setChangingWithAdjacent(false);
        break;
    case Difficulty::CHANTILLY :
        d.setName(Difficulty::NONE);
        d.setBlocking(false);
        d.setSweetPresence(true);
        d.setChangingWithAdjacent(false);
        break;
    case Difficulty::CAGE :
        d.setName(Difficulty::NONE);
        d.setBlocking(false);
        break;
    /* Rajouter ici les nouvelles difficultés
     * ATTENTION : Veiller à rajouter la difficulté dans l'énum
     */
    default:
        throw ValueError<int>("difficulty.cpp"
                    , "Constructor Difficulty::Difficulty(Name)"
                    , "Invalid difficulty value"
                    , name);
        break;
    }
    return d;
}
