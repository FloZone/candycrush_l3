#ifndef SWEET_H
#define SWEET_H
#include <SFML/Graphics.hpp>
/*
 * Nombre de couleurs (sans le NONE)
 * à mettre à jour lors de l'ajout d'une couleur
 *
 */
#define NB_COLORS_S 6

class Sweet
{
public:
    enum Color
    {
        NONE,
        RED,
        BLUE,
        GREEN,
        ORANGE,
        PURPLE,
        YELLOW
        /*
         * Rajouter ici les nouvelles couleurs
         * Ne pas oublier de changer la valeur de #define NB_COLORS_S
         *
         */
    };

    Sweet(Color _color = NONE);
    ~Sweet();

    Color getColor();
    void setColor(Color _color);

private:
    Color color;
};

#endif // SWEET_H
