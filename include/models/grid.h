#ifndef GRID_H
#define GRID_H

#include <iostream>

#include "../exceptions/error.h"
#include "../exceptions/error_message.h"
#include "../exceptions/error_value.h"
#include "../util/util.h"
#include "element.h"
#include "playable.h"
#include "obstacle.h"

#define THIRD_LINE 2
#define THIRD_COLUMN 2
#define MIN_NB_COLORS_S 3

class Grid
{
public:
    Grid(int _sizeX = 3, int _sizeY = 3);
    Grid(const Grid & _grid);
    ~Grid();
    Grid & operator=(const Grid & _grid);

    int getSizeX() const;

    int getSizeY() const ;

    Element* getCell(int x, int y) const;

    Element*** getMatrice();

    void initialize(int x, int y, int nbColor
                    , bool createObstacle = false
                    , Difficulty::Name diffName = Difficulty::NONE);
    void reinitializeAllSweets(int nbColor);

    bool isSweetAuthorized(int x, int y);

    bool coup_possible();

    void swapSweet(int,int,int,int);
    void burst(int,int);
    void changeDifficulty(int,int);
    bool decaler_diagonales(int);
    bool generer_bonbon(int,int);

    int get_nb_gelatine();
    int get_nb_chantilly();
    int get_nb_cage();

    friend std::ostream& operator<<(std::ostream& out, const Grid& grid);

private:
    int sizeX;
    int sizeY;
    Element*** matrice;

    int nb_gelatine;
    int nb_chantilly;
    int nb_cage;

    void generateSweet(int x, int y, int nbColor, bool naive = false);
};

#endif // GRID_H
