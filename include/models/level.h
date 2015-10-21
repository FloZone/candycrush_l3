#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <yaml-cpp/yaml.h>

#include "../exceptions/error.h"
#include "../exceptions/error_message.h"
#include "../exceptions/error_value.h"

#include "../controller/observable.h"
#include "grid.h"

#define MAX_SIDE_SIZE 9
#define MIN_SIDE_SIZE 3

#define MOUVEMENT_NULL -1
#define MOUVEMENT_VALIDE 1

#define OBJECTIVE_FAILURE -1
#define OBJECTIVE_SUCCESS 1
#define OBJECTIVE_REACHABLE 0

class Level : public Observable
{
public:
    enum Objective {
        NONE,
        GELATINE,
        CHANTILLY,
        CAGE
        /*
         * Rajouter ici les nouveaux objectifs
         */
        };

    Level(std::string _level = "./levels/training.yml");
    ~Level();
    Level(const Level & _level);
    Level & operator=(const Level & _level);

    /* Accesseurs */
    std::string getName()const;
    int getScore() const;
    int getScoreObjective() const;
    int getHits() const;
    int getHitsObjective() const;
    Objective getObjective() const;
    Grid * getGrid() const;
    int getNbColor() const;

    /* Implémentation des fonctions d'Observable */
    void notifyObserver();
    void notifyObserver(bool, int, int, int, int);
    void notifyMovementObserver(int x1, int y1, int x2, int y2);
    void update(bool drag,int x1, int y1, int x2, int y2);

    /* Fonctions */
    int mouvement(bool, int,int,int,int);
    int etat_objectif() const;
    bool decaler_diagonales(int x);
    bool decaler_haut(int);


private:

    std::string name;
    unsigned int nb_color;
    unsigned int score_objective;
    unsigned int score;
    unsigned int hits_objective;
    unsigned int hits;
    Objective objective;
    Grid * grid;

    bool alignement(int,int);
    int test_alignement_horizontal(int,int,int&,int&);
    int test_alignement_vertical(int,int,int&,int&);
    void alignement3horizontal(int,int,int);
    void alignement3vertical(int,int,int);
    void alignement4horizontal(int);
    void alignement4vertical(int);
    void alignement5_3();
    void alignement5(int,int);
    void alignement3_3(int,int);
    void decalage();

};

#endif // LEVEL_H
