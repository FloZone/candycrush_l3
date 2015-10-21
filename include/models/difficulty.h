#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include "../exceptions/error_value.h"

class Difficulty
{
public:
    enum Name {
        NONE,
        GEL_1,
        GEL_2,
        CHANTILLY,
        CAGE
        /* Rajouter ici les nouveaux nom de difficulté
         * ATTENTION : Veiller à rajouter la difficulté dans le constructeur
         */
    };

    Difficulty(Name _name = NONE);

    Name getName();
    bool isBlocking();
    bool isSweetPresence();
    bool isChangingWithAdjacent();

    Difficulty change();

private:

    Name name;
    bool blocking;
    bool sweetPresence;
    bool changingWithAdjacent;

    void setName(Name _name);
    void setBlocking(bool _blocking);
    void setSweetPresence(bool _sweetPresence);
    void setChangingWithAdjacent(bool _changingWithAdjacent);
};

#endif // DIFFICULTY_H
