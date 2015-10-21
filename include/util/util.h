#ifndef UTIL_H
#define UTIL_H

#define NOT_FOUND -1

/*
 * Retourne un nombre aléatoire entre deux bornes
 */
int randomInt(int min, int max);

/*
 * Retourne l'indice auquel l'élément a été trouvé
 * -1 si non trouvé
 */
//template <class T>
//int findIn(const T tab[], int size, const T &elem);
int findIn(const int tab[], int size, const int elem);

/*
 * Permute deux éléments d'un tableau
 */
//template <class T>
//void permute(T tab[], int ind_1, int ind_2);
void permute(int tab[], int ind_1, int ind_2);

#endif // UTIL_H
