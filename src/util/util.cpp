#include <cstdlib>
#include <ctime>
#include "util/util.h"

int randomInt(int min, int max)
{
    return (rand() % (max - min) + min);
}

int findIn(const int tab[], int size, const int elem)
{
    for(int i = 0; i < size; i++)
        if(elem == tab[i])
            return i;

    return NOT_FOUND;
}

void permute(int tab[], int ind_1, int ind_2)
{
    int aux;

    if(ind_1 != ind_2)
    {
        aux = tab[ind_1];
        tab[ind_1] = tab[ind_2];
        tab[ind_2] = aux;
    }
}
