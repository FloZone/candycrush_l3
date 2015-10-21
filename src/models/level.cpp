#include "models/level.h"

using namespace std;


/*
 * Constructeur
 */
Level::Level(string _level)
    : score(0), hits(0), grid(NULL)
{
    int sizeX, sizeY;
    YAML::Node file;

    observer = NULL;

    // Test file
    try
    {
        file = YAML::LoadFile(_level);
    }
    catch(exception &e)
    {
        throw ValueError<string>("level.cpp"
                                 ,"Constructor Level::Level(string)"
                                 , e.what()
                                 , _level);
    }

    // Name of the level
    name = file["name"].as<string>();

    // Test nb of color
    if(file["nb_color"].as<int>() > NB_COLORS_S || file["nb_color"].as<int>() < 2 )
    {
        throw ValueError<int>("level.cpp"
                              , "Constructor Level::Level(string)"
                              , "Wrong number of used colors. See the maximum value NB_COLORS_S"
                              , file["nb_color"].as<int>());
    }
    else
    {
        nb_color = file["nb_color"].as<int>();
    }

    // Score to reach
    score_objective = file["score_obj"].as<int>();

    // Hits remaining
    if(file["hits_obj"].as<int>() == 0)
    {
        hits_objective = -1;
    }
    else
    {
        hits_objective = file["hits_obj"].as<int>();
    }

    // Test objective
    if(file["objective"].as<int>() == 0)
        objective = NONE;
    else if(file["objective"].as<int>() == 1)
        objective = GELATINE;
    else if(file["objective"].as<int>() == 2)
        objective = CHANTILLY;
    else if(file["objective"].as<int>() == 3)
        objective = CAGE;
    else
        objective = NONE;

    // Test size of grid
    sizeX = (file["size"][0].as<int>());
    sizeY = (file["size"][1].as<int>());
    if(sizeX > MAX_SIDE_SIZE)
        throw ValueError<int>("level.cpp"
                              , "Constructor Level::Level(string)"
                              , "The size of x-axis is too big. See the maximum value MAX_SIDE_SIZE"
                              , sizeX);
    else if(sizeX < MIN_SIDE_SIZE)
        throw ValueError<int>("level.cpp"
                              , "Constructor Level::Level(string)"
                              , "The size of x-axis is too small. See the minimum value MIN_SIDE_SIZE"
                              , sizeX);
    else if(sizeY > MAX_SIDE_SIZE)
        throw ValueError<int>("level.cpp"
                              , "Constructor Level::Level(string)"
                              , "The size of y-axis is too big. See the maximum value MAX_SIDE_SIZE"
                              , sizeY);
    else if(sizeY < MIN_SIDE_SIZE)
        throw ValueError<int>("level.cpp"
                              , "Constructor Level::Level(string)"
                              , "The size of y-axis is too small. See the minimum value MIN_SIDE_SIZE"
                              , sizeY);

    grid = new Grid(sizeX, sizeY);

    // Test bonus
    const YAML::Node& bonus = file["grid"];
    for(unsigned int i = 0; i < bonus.size(); ++i)
    {
        int x = bonus[i][0].as<int>();
        int y = bonus[i][1].as<int>();
        int type = bonus[i][2].as<int>();
        int diff = bonus[i][3].as<int>();

        // Vérifier les coordonnées de la case
        if(x >= sizeX)
            throw ValueError<int>("level.cpp"
                                  , "Constructor Level::Level(string)"
                                  , "The x-axis bonus cell is too big. See the maximum grid x-axis size"
                                  , x);
        else if(x < 0)
            throw ValueError<int>("level.cpp"
                                  , "Constructor Level::Level(string)"
                                  , "The size of x-axis is too small. See the minimum value MIN_SIDE_SIZE"
                                  , x);
        else if(y >= sizeY)
            throw ValueError<int>("level.cpp"
                                  , "Constructor Level::Level(string)"
                                  , "The y-axis bonus cell is too big. See the maximum grid y-axis size"
                                  , y);
        else if(y < 0)
            throw ValueError<int>("level.cpp"
                                  , "Constructor Level::Level(string)"
                                  , "The size of y-axis is too small. See the minimum value MIN_SIDE_SIZE"
                                  , y);
        // Case obstacle
        if(type == 1)
        {
            // Créer un obstacle
            grid -> initialize(x, y, nb_color, true, (Difficulty::Name)diff);
            // Gérer ici les différents niveaux d'obstacle
        }
        // Case jouable
        else if(type == 0)
        {
            grid -> initialize(x, y, nb_color, false, (Difficulty::Name)diff);
            // Gérer ici les différents niveaux de difficulté (gélatine, etc)

        }
        // Type inconnu
        else
        {
            throw ValueError<int>("level.cpp"
                                  , "Constructor Level::Level(string)"
                                  , "The bonus cell type is unknown. 0: playable, 1: obstacle."
                                  , x);
        }
    }

    // Initialisation du reste de grid
    for(int cpt_y = 0; cpt_y < sizeY; cpt_y++)
    {
        for(int cpt_case = 0; cpt_case < sizeX; cpt_case++)
        {
            grid -> initialize(cpt_case, cpt_y, nb_color);
        }
    }

}
Level::~Level()
{
    delete grid;
}


/*
 * Coplien
 */
Level::Level(const Level & _level)
{
    this -> name = _level.name;
    this -> nb_color = _level.nb_color;
    this -> score_objective = _level.score_objective;
    this -> score = _level.score;
    this -> hits_objective = _level.hits_objective;
    this -> hits = _level.hits;
    this -> objective = _level.objective;
    this -> grid = new Grid(*(_level.grid));
}
Level & Level::operator=(const Level & _level)
{
    if(this != & _level)
    {
        if(grid)
        {
            delete grid;
        }
        this -> name = _level.name;
        this -> nb_color = _level.nb_color;
        this -> score_objective = _level.score_objective;
        this -> score = _level.score;
        this -> hits_objective = _level.hits_objective;
        this -> hits = _level.hits;
        this -> objective = _level.objective;

        this -> grid = new Grid(*(_level.grid));
    }
    return *this;
}

/*
 * Accesseurs
 */
string Level::getName()const
{
    return name;
}
int Level::getScore() const
{
    return score;
}
int Level::getScoreObjective() const
{
    return score_objective;
}
int Level::getHits() const
{
    return hits;
}
int Level::getHitsObjective() const
{
    return hits_objective;
}
Level::Objective Level::getObjective() const
{
    return objective;
}
Grid * Level::getGrid() const
{
    return grid;
}
int Level::getNbColor() const
{
    return nb_color;
}

/*
 * Implémentation des fonctions d'Oservable
 */
void Level::notifyObserver()
{
    observer -> update(*this);
}

void Level::notifyObserver(bool drag, int x1, int y1, int x2, int y2)
{
    observer -> update(*this,drag,false, x1, y1, x2, y2);
}
void Level::update(bool drag, int x1, int y1, int x2, int y2)
{
    mouvement(drag,x1, y1, x2, y2);
}

/*
 * Fonctions
 *
 */

// Gère le mouvement effectué par l'utilisateur
int Level::mouvement(bool drag, int depart_x, int depart_y, int arrivee_x, int arrivee_y)
{
    // Si les cases de départ et d'arrivée sont valides
    if( grid -> getCell(depart_x, depart_y) -> hasSweet()
        && !(grid -> getCell(depart_x, depart_y) -> isBlocking())
        && grid -> getCell(arrivee_x, arrivee_y) -> hasSweet()
        && !(grid -> getCell(arrivee_x, arrivee_y) -> isBlocking()) )
    {
        // Echanger les bonbons
        grid->swapSweet(depart_x, depart_y, arrivee_x, arrivee_y);
        // Afficher
        notifyObserver(drag, depart_x,depart_y,arrivee_x,arrivee_y);
        // Tester et effectuer les alignements sur la case d'arrivée
        bool coup_valide(false);
        if(alignement(arrivee_x,arrivee_y))
        {
            coup_valide = true;
        }
        // Même chose pour la case de départ
        if(alignement(depart_x, depart_y))
        {
            coup_valide = true;
        }


        // Si le coup n'était pas valide
        if(!coup_valide)
        {
            // Remettre les deux bonbons comme précédemment
            grid->swapSweet(depart_x, depart_y, arrivee_x, arrivee_y);
            // Afficher
            notifyObserver(drag, depart_x,depart_y,arrivee_x,arrivee_y);
            return MOUVEMENT_NULL;
        }
        // Sinon le coup était valide
        else
        {
            // Mettre à jour le nombre de coups
            ++hits;
            // Décaler les bonbons
            decalage();
            // Tant qu'il reste des alignements à détruire
            bool alignement_restant(false);
            do
            {
                // Parcourir toute la grille
                alignement_restant = false;
                for(int cpt_x(0); cpt_x < grid->getSizeX(); ++cpt_x)
                {
                    for(int cpt_y(grid->getSizeY()-1); cpt_y >= 0; --cpt_y)
                    {
                        // Si la case est valide et qu'elle fait un alignement
                        if( grid -> getCell(cpt_x, cpt_y) -> hasSweet()
                            && !(grid -> getCell(cpt_x, cpt_y) -> isBlocking())
                            && alignement(cpt_x, cpt_y) )
                        {
                            // Faire les décalages nécessaires
                            decalage();
                            alignement_restant = true;
                        }
                    }
                }
            } while(alignement_restant);
            return MOUVEMENT_VALIDE;
        }
    }
    // Sinon le mouvement est invalide
    else
    {
        return MOUVEMENT_NULL;
    }
}

// Teste et effectue les alignements de la case (x,y)
bool Level::alignement(int x, int y)
{
    int x_mini(x), x_maxi(x);
    int y_mini(y), y_maxi(y);

    // Tester les alignements
    int cpt_bonbon_horizontal = test_alignement_horizontal(x, y, x_mini, x_maxi);
    int cpt_bonbon_vertical = test_alignement_vertical(x, y, y_mini, y_maxi);


    // Alignements spéciaux

    // Alignement en T de 5 et 3
    if( ((cpt_bonbon_horizontal == 5) && (cpt_bonbon_vertical == 3))
        || ((cpt_bonbon_horizontal == 3) && (cpt_bonbon_vertical == 5)) )
    {
        // Faire l'alignement
        alignement5_3();
        return true;
    }

    // Alignement de 5 bonbons ou plus (arrive lors de la génération)
    if( (cpt_bonbon_horizontal >= 5) || (cpt_bonbon_vertical >= 5) )
    {
        // Faire l'alignement
        alignement5(x, y);
        return true;
    }

    // Alignement en L ou en T
    else if( ((cpt_bonbon_horizontal == 3) && (cpt_bonbon_vertical == 3))
             || ((cpt_bonbon_horizontal == 4) && (cpt_bonbon_vertical == 3))
             || ((cpt_bonbon_horizontal == 4) && (cpt_bonbon_vertical == 4)) )
    {
        // Faire l'alignement
        alignement3_3(x, y);
        return true;
    }


    // Alignements horizontaux

    // Alignement de 3 horizontal
    if(cpt_bonbon_horizontal == 3)
    {
        // Faire l'alignement
        alignement3horizontal(y, x_mini, x_maxi);
        return true;
    }

    // Alignement de 4 horizontal
    else if(cpt_bonbon_horizontal == 4)
    {
        // Faire l'alignement
        alignement4horizontal(y);
        return true;
    }


    // Alignements verticaux

    // Alignement de 3 vertical
    if(cpt_bonbon_vertical == 3)
    {
        // Faire l'alignement
        alignement3vertical(x, y_mini, y_maxi);
        return true;
    }

    // Alignement de 4 vertical
    else if(cpt_bonbon_vertical == 4)
    {
        // Faire l'alignement
        alignement4vertical(x);
        return true;
    }


    // Si on arrive ici, le coup n'était pas valide;
    return false;
}


// Tester la présence d'un alignement horizontal
int Level::test_alignement_horizontal(int x, int y, int & x_mini, int & x_maxi)
{
    int cpt_bonbon(1);

    // Sur les cases précédentes
    int x_aux(x-1);
    // Tant que la case précédente comporte un bonbon de même couleur
    while( x_aux >= 0
           && grid -> getCell(x_aux, y) -> hasSweet()
           && grid -> getCell(x, y) -> hasSweet()
           && ((Playable*)grid -> getCell(x_aux, y)) -> getSweet() -> getColor() == ((Playable*)grid -> getCell(x, y)) -> getSweet() -> getColor() )
    {
        // Augmenter le nombre de bonbon à détruire
        ++cpt_bonbon;
        // Mettre à jour la plus petite case pour la destruction
        x_mini = x_aux;
        // Regarder la case précédente
        --x_aux;
    }
    // Sur les cases suivantes
    x_aux = x + 1;
    // Tant que la case suivante comporte un bonbon de même couleur
    while( x_aux < grid -> getSizeX()
           && grid -> getCell(x_aux, y) -> hasSweet()
           && grid -> getCell(x, y) -> hasSweet()
           && ((Playable*)grid -> getCell(x_aux, y)) -> getSweet() -> getColor() == ((Playable*)grid -> getCell(x, y)) -> getSweet() -> getColor() )
    {
        // Augmenter le nombre de bonbon à détruire
        ++cpt_bonbon;
        // Mettre à jour la plus grande case pour la destruction
        x_maxi = x_aux;
        // Regarder la case suivante
        ++x_aux;
    }

    return cpt_bonbon;
}

// Tester la présence d'un alignement vertical
int Level::test_alignement_vertical(int x, int y, int & y_mini, int & y_maxi)
{
    int cpt_bonbon(1);

    // Sur les cases précédentes
    int y_aux(y-1);
    // Tant que la case précédente comporte un bonbon de même couleur
    while( y_aux >= 0
           && grid -> getCell(x, y_aux) -> hasSweet()
           && grid -> getCell(x, y) -> hasSweet()
           && ((Playable*)grid -> getCell(x, y_aux)) -> getSweet() -> getColor() == ((Playable*)grid -> getCell(x, y)) -> getSweet() -> getColor() )
    {
        // Augmenter le nombre de bonbon à détruire
        ++cpt_bonbon;
        // Mettre à jour la plus petite case pour la destruction
        y_mini = y_aux;
        // Sur les cases suivantes
        --y_aux;
    }
    // Regarder la case précédente
    y_aux = y + 1;
    // Tant que la case suivante comporte un bonbon de même couleur
    while( y_aux < grid -> getSizeY()
           && grid -> getCell(x, y_aux) -> hasSweet()
           && grid -> getCell(x, y) -> hasSweet()
           && ((Playable*)grid -> getCell(x, y_aux)) -> getSweet() -> getColor() == ((Playable*)grid -> getCell(x, y)) -> getSweet() -> getColor() )
    {
        // Augmenter le nombre de bonbon à détruire
        ++cpt_bonbon;
        // Mettre à jour la plus grande case pour la destruction
        y_maxi = y_aux;
        // Regarder la case suivante
        ++y_aux;
    }

    return cpt_bonbon;
}


// Alignement de 3 bonbons horizontaux
void Level::alignement3horizontal(int y, int x_mini, int x_maxi)
{
    // Parcourir toutes les cases entre mini et maxi
    for(int cpt_x(x_mini); cpt_x <= x_maxi; ++cpt_x)
    {
        // Mise à jour du score
        score += 20;
        // Détruire le bonbon
        grid->burst(cpt_x, y);
        // Afficher
        notifyObserver();
    }

    // Regarder les cases à côté de l'alignement
    // Si la case d'avant a une chantilly
    if( x_mini > 0
        && grid->getCell(x_mini-1,y) -> playable()
        && ((Playable*)grid->getCell(x_mini-1,y)) -> getDifficulty().isChangingWithAdjacent())
    {
        // Mettre à jour le score
        score += 30;
        // Détruire la chantilly
        grid->changeDifficulty(x_mini-1, y);
        // Afficher
        notifyObserver();
    }
    // Si la case d'après a une chantilly
    if( x_maxi < (grid->getSizeX() - 1)
        && grid -> getCell(x_maxi+1,y) -> playable()
        && ((Playable*)grid -> getCell(x_maxi+1,y)) -> getDifficulty().isChangingWithAdjacent() )

    {
        // Mettre à jour le score
        score += 30;
        // Détruire la chantilly
        grid->changeDifficulty(x_maxi+1, y);
        // Afficher
        notifyObserver();
    }
    // Ligne au dessus
    if(y > 0)
    {
        for(int cpt_x(x_mini); cpt_x <= x_maxi; ++cpt_x)
        {
            // Si une case contient une chantilly
            if( grid -> getCell(cpt_x, y-1) -> playable()
                && ((Playable*)grid->getCell(cpt_x, y-1)) -> getDifficulty().isChangingWithAdjacent() )
            {
                // Mettre à jour le score
                score += 30;
                // Détruire la chantilly
                grid->changeDifficulty(cpt_x, y - 1);
                // Afficher
                notifyObserver();
            }
        }
    }
    // Ligne au dessous
    if( y < (grid->getSizeY() - 1) )
    {
        for(int cpt_x(x_mini); cpt_x <= x_maxi; ++cpt_x)
        {
            // Si une case contient une chantilly
            if( grid->getCell(cpt_x, y+1) -> playable()
                && ((Playable*)grid->getCell(cpt_x, y+1)) -> getDifficulty().isChangingWithAdjacent() )
            {
                // Mettre à jour le score
                score += 30;
                // Détruire la chantilly
                grid->changeDifficulty(cpt_x, y + 1);
                // Afficher
                notifyObserver();
            }
        }
    }

}

// Alignement de 3 bonbons verticaux
void Level::alignement3vertical(int x, int y_mini, int y_maxi)
{
    // Parcourir toutes les cases entre mini et maxi
    for(int cpt_y(y_mini); cpt_y <= y_maxi; ++cpt_y)
    {
        // Mise à jour du score
        score += 20;
        // Détruire le bonbon
        grid->burst(x, cpt_y);
        // Afficher
        notifyObserver();
    }

    // Regarder les cases à côté de l'alignement
    // Si la case d'avant a une chantilly
    if( y_mini > 0
        && grid->getCell(x,y_mini-1) -> playable()
        && ((Playable*)grid->getCell(x,y_mini-1)) -> getDifficulty().isChangingWithAdjacent())
    {
        // Mettre à jour le score
        score += 30;
        // Détruire la chantilly
        grid->changeDifficulty(x, y_mini-1);
        // Afficher
        notifyObserver();
    }
    // Si la case d'après a une chantilly
    if( y_maxi < (grid->getSizeY() - 1)
        && grid->getCell(x, y_maxi+1) -> playable()
        && ((Playable*)grid->getCell(x,y_maxi+1)) -> getDifficulty().isChangingWithAdjacent() )

    {
        // Mettre à jour le score
        score += 30;
        // Détruire la chantilly
        grid->changeDifficulty(x, y_maxi+1);
        // Afficher
        notifyObserver();
    }
    // Colonne à gauche
    if(x > 0)
    {
        for(int cpt_y(y_mini); cpt_y <= y_maxi; ++cpt_y)
        {
            // Si une case contient une chantilly
            if( grid->getCell(x-1, cpt_y) -> playable()
                && ((Playable*)grid->getCell(x-1, cpt_y)) -> getDifficulty().isChangingWithAdjacent() )
            {
                // Mettre à jour le score
                score += 30;
                // Détruire la chantilly
                grid->changeDifficulty(x - 1, cpt_y);
                // Afficher
                notifyObserver();
            }
        }
    }
    // Colonne à droite
    if( x < (grid->getSizeX() - 1) )
    {
        for(int cpt_y(y_mini); cpt_y <= y_maxi; ++cpt_y)
        {
            // Si une case contient une chantilly
            if( grid->getCell(x+1, cpt_y) -> playable()
                && ((Playable*)grid->getCell(x+1, cpt_y)) -> getDifficulty().isChangingWithAdjacent() )
            {
                // Mettre à jour le score
                score += 30;
                // Détruire la chantilly
                grid->changeDifficulty(x + 1, cpt_y);
                // Afficher
                notifyObserver();
            }
        }
    }
}

// Alignement de 4 bonbons horizontaux
void Level::alignement4horizontal(int y)
{
    // Mise à jour du score
    score += 100;

    // Détruire toute la ligne
    for(int cpt_x(0); cpt_x < grid->getSizeX(); ++cpt_x)
    {
        // Si la case a un bonbon
        if( grid -> getCell(cpt_x, y) -> hasSweet() )
        {
            // Mise à jour du score
            score += 50;
            // Détruire le bonbon
            grid->burst(cpt_x, y);
            // Afficher
            notifyObserver();
        }
        else if( grid->getCell(cpt_x, y)->playable()
                 && ((Playable*)grid->getCell(cpt_x, y)) -> getDifficulty().isChangingWithAdjacent() )
        {
            // Mise à jour du score
            score += 30;
            // Détruire la chantilly
            grid->changeDifficulty(cpt_x, y);
            // Afficher
            notifyObserver();
        }
    }

    // Regarder la chantilly sur la ligne au dessus
    if(y > 0)
    {
        for(int cpt_x(0); cpt_x < grid->getSizeX(); ++cpt_x)
        {
            // Si une case contient une chantilly
            if( grid->getCell(cpt_x, y-1)->playable()
                && ((Playable*)grid->getCell(cpt_x, y-1)) -> getDifficulty().isChangingWithAdjacent() )
            {
                // Mise à jour du score
                score += 30;
                // Détruire la chantilly
                grid->changeDifficulty(cpt_x, y-1);
                // Afficher
                notifyObserver();
            }
        }
    }
    // Regarder la chantilly sur la ligne au dessous
    if( y < (grid->getSizeY() - 1) )
    {
        for(int cpt_x(0); cpt_x < grid->getSizeX(); ++cpt_x)
        {
            // Si une case contient une chantilly
            if( grid->getCell(cpt_x, y+1)->playable()
                && ((Playable*)grid->getCell(cpt_x, y+1)) -> getDifficulty().isChangingWithAdjacent() )
            {
                // Mise à jour du score
                score += 30;
                // Détruire la chantilly
                grid->changeDifficulty(cpt_x, y+1);
                // Afficher
                notifyObserver();
            }
        }
    }
}

// Alignement de 4 bonbons verticaux
void Level::alignement4vertical(int x)
{
    // Mise à jour du score
    score += 100;

    // Détruire toute la colonne
    for(int cpt_y(0); cpt_y < grid->getSizeY(); ++cpt_y)
    {
        // Si la case a un bonbon
        if( grid -> getCell(x, cpt_y) -> hasSweet() )
        {
            // Mise à jour du score
            score += 50;
            // Détruire le bonbon
            grid->burst(x, cpt_y);
            // Afficher
            notifyObserver();
        }
        else if( grid->getCell(x, cpt_y)->playable()
                 && ((Playable*)grid->getCell(x, cpt_y)) -> getDifficulty().isChangingWithAdjacent() )
        {
            // Mise à jour du score
            score += 30;
            // Détruire la chantilly
            grid->changeDifficulty(x, cpt_y);
            // Afficher
            notifyObserver();
        }
    }

    // Regarder la chantilly sur la colonne à gauche
    if(x > 0)
    {
        for(int cpt_y(0); cpt_y < grid->getSizeY(); ++cpt_y)
        {
            // Si une case contient une chantilly
            if( grid->getCell(x-1, cpt_y)->playable()
                && ((Playable*)grid->getCell(x-1, cpt_y)) -> getDifficulty().isChangingWithAdjacent() )
            {
                // Mise à jour du score
                score += 30;
                // Détruire la chantilly
                grid->changeDifficulty(x-1, cpt_y);
                // Afficher
                notifyObserver();
            }
        }
    }
    // Regarder la chantilly sur la colonne à droite
    if( x < (grid->getSizeX() - 1) )
    {
        for(int cpt_y(0); cpt_y < grid->getSizeY(); ++cpt_y)
        {
            // Si une case contient une chantilly
            if( grid->getCell(x+1, cpt_y)->playable()
                && ((Playable*)grid->getCell(x+1, cpt_y)) -> getDifficulty().isChangingWithAdjacent() )
            {
                // Mise à jour du score
                score += 30;
                // Détruire la chantilly
                grid->changeDifficulty(x+1, cpt_y);
                // Afficher
                notifyObserver();
            }
        }
    }
}

// Alignement en T de 5 et 3
void Level::alignement5_3()
{
    // Mise à jour du score
    score += 1000;

    // Parcourir toute la grille
    for(int cpt_y(0); cpt_y < grid->getSizeY(); ++cpt_y)
    {
        for(int cpt_x(0); cpt_x < grid->getSizeX(); ++cpt_x)
        {

            // Si la case contient un bonbon
            if( grid -> getCell(cpt_x, cpt_y) -> hasSweet() )
            {
                // Mise à jour du score
                score += 100;
                // Détruire le bonbon
                grid->burst(cpt_x, cpt_y);
                // Afficher
                notifyObserver();
            }
            // Sinon s'il s'agit d'une chantilly
            else if( grid->getCell(cpt_x, cpt_y)->playable()
                     && ((Playable*)grid->getCell(cpt_x, cpt_y)) -> getDifficulty().isChangingWithAdjacent() )
            {
                // Mise à jour du score
                score += 30;
                // Détruire la chantilly
                grid->changeDifficulty(cpt_x, cpt_y);
                // Afficher
                notifyObserver();
            }

        } // END BOUCLE FOR X
    } // END BOUCLE FOR Y
}

// Alignement de 5 bonbons
void Level::alignement5(int x, int y)
{
    // Mise à jour du score
    score += 500;

    // Stocker la couleur à tester
    Sweet::Color color = ((Playable*)grid -> getCell(x, y)) -> getSweet() -> getColor();

    // Parcourir toute la grille
    for(int cpt_y(0); cpt_y < grid->getSizeY(); ++cpt_y)
    {
        for(int cpt_x(0); cpt_x < grid->getSizeX(); ++cpt_x)
        {
            // Si la case est valide et que le bonbon est de la même couleur
            if( grid -> getCell(cpt_x, cpt_y) -> hasSweet()
                && ((Playable*)grid -> getCell(cpt_x, cpt_y)) -> getSweet() -> getColor() == color )
            {

                // Mise à jour du score
                score += 100;
                // Détruire le bonbon
                grid->burst(cpt_x, cpt_y);
                // Afficher
                notifyObserver();

                // Regarder s'il y a de la chantilly à côté
                // Au dessus
                if( cpt_y > 0
                    && grid->getCell(cpt_x, cpt_y-1)->playable()
                    && ((Playable*)grid->getCell(cpt_x, cpt_y-1)) -> getDifficulty().isChangingWithAdjacent() )
                {
                    // Mise à jour du score
                    score += 30;
                    // Détruire la chantilly
                    grid->changeDifficulty(cpt_x, cpt_y-1);
                    // Afficher
                    notifyObserver();
                }
                // Au dessous
                if( cpt_y < (grid->getSizeY() - 1)
                    && grid->getCell(cpt_x, cpt_y+1)->playable()
                    && ((Playable*)grid->getCell(cpt_x, cpt_y+1)) -> getDifficulty().isChangingWithAdjacent() )
                {
                    // Mise à jour du score
                    score += 30;
                    // Détruire la chantilly
                    grid->changeDifficulty(cpt_x, cpt_y+1);
                    // Afficher
                    notifyObserver();
                }
                // A gauche
                if( cpt_x > 0
                    && grid->getCell(cpt_x-1, cpt_y)->playable()
                    && ((Playable*)grid->getCell(cpt_x-1, cpt_y)) -> getDifficulty().isChangingWithAdjacent() )
                {
                    // Mise à jour du score
                    score += 30;
                    // Détruire la chantilly
                    grid->changeDifficulty(cpt_x-1, cpt_y);
                    // Afficher
                    notifyObserver();
                }
                // A droite
                if( cpt_x < (grid->getSizeX() - 1)
                    && grid->getCell(cpt_x+1, cpt_y)->playable()
                    && ((Playable*)grid->getCell(cpt_x+1, cpt_y)) -> getDifficulty().isChangingWithAdjacent() )
                {
                    // Mise à jour du score
                    score += 30;
                    // Détruire la chantilly
                    grid->changeDifficulty(cpt_x+1, cpt_y);
                    // Afficher
                    notifyObserver();
                }

            } // END IF CASE VALIDE

        } // END BOUCLE FOR X
    } // END BOUCLE FOR Y
}

// Alignement en L ou T
void Level::alignement3_3(int x, int y)
{
    // Mise à jour du score
    score += 500;

    // Détruire toute la ligne
    for(int cpt_x(0); cpt_x < grid->getSizeX(); ++cpt_x)
    {
        // Si la case a un bonbon
        if( grid -> getCell(cpt_x, y) -> hasSweet() )
        {
            // Mise à jour du score
            score += 100;
            // Détruire le bonbon
            grid->burst(cpt_x, y);
            // Afficher
            notifyObserver();
        }
        else if( grid->getCell(cpt_x, y)->playable()
                 && ((Playable*)grid->getCell(cpt_x, y)) -> getDifficulty().isChangingWithAdjacent() )
        {
            // Mise à jour du score
            score += 30;
            // Détruire la chantilly
            grid->changeDifficulty(cpt_x, y);
            // Afficher
            notifyObserver();
        }
    }
    // Détruire toute la colonne
    for(int cpt_y(0); cpt_y < grid->getSizeY(); ++cpt_y)
    {
        // Si la case a un bonbon
        if( grid -> getCell(x, cpt_y) -> hasSweet() )
        {
            // Mise à jour du score
            score += 100;
            // Détruire le bonbon
            grid->burst(x, cpt_y);
            // Afficher
            notifyObserver();
        }
        else if( grid->getCell(x, cpt_y)->playable()
                 && ((Playable*)grid->getCell(x, cpt_y)) -> getDifficulty().isChangingWithAdjacent() )
        {
            // Mise à jour du score
            score += 30;
            // Détruire la chantilly
            grid->changeDifficulty(x, cpt_y);
            // Afficher
            notifyObserver();
        }
    }

    // Regarder la chantilly sur la ligne au dessus
    if(y > 0)
    {
        for(int cpt_x(0); cpt_x < grid->getSizeX(); ++cpt_x)
        {
            // Si une case contient une chantilly
            if( grid->getCell(cpt_x, y-1)->playable()
                && ((Playable*)grid->getCell(cpt_x, y-1)) -> getDifficulty().isChangingWithAdjacent() )
            {
                // Mise à jour du score
                score += 30;
                // Détruire la chantilly
                grid->changeDifficulty(cpt_x, y-1);
                // Afficher
                notifyObserver();
            }
        }
    }

    // Regarder la chantilly sur la ligne au dessous
    if( y < (grid->getSizeY() - 1) )
    {
        for(int cpt_x(0); cpt_x < grid->getSizeX(); ++cpt_x)
        {
            // Si une case contient une chantilly
            if( grid->getCell(cpt_x, y+1)->playable()
                && ((Playable*)grid->getCell(cpt_x, y+1)) -> getDifficulty().isChangingWithAdjacent() )
            {
                // Mise à jour du score
                score += 30;
                // Détruire la chantilly
                grid->changeDifficulty(cpt_x, y+1);
                // Afficher
                notifyObserver();
            }
        }
    }

    // Regarder la chantilly sur la colonne à gauche
    if(x > 0)
    {
        for(int cpt_y(0); cpt_y < grid->getSizeY(); ++cpt_y)
        {
            // Si une case contient une chantilly
            if( grid->getCell(x-1, cpt_y)->playable()
                && ((Playable*)grid->getCell(x-1, cpt_y)) -> getDifficulty().isChangingWithAdjacent() )
            {
                // Mise à jour du score
                score += 30;
                // Détruire la chantilly
                grid->changeDifficulty(x-1, cpt_y);
                // Afficher
                notifyObserver();
            }
        }
    }
    // Regarder la chantilly sur la colonne à droite
    if( x < (grid->getSizeX() - 1) )
    {
        for(int cpt_y(0); cpt_y < grid->getSizeY(); ++cpt_y)
        {
            // Si une case contient une chantilly
            if( grid->getCell(x+1, cpt_y)->playable()
                && ((Playable*)grid->getCell(x+1, cpt_y)) -> getDifficulty().isChangingWithAdjacent() )
            {
                // Mise à jour du score
                score += 30;
                // Détruire la chantilly
                grid->changeDifficulty(x+1, cpt_y);
                // Afficher
                notifyObserver();
            }
        }
    }
}

// Décale les bonbons avec les cases diagonales
bool Level::decaler_diagonales(int x)
{
    // Pour chaque case de la colonne
    for(int cpt_y(grid->getSizeY() - 1); cpt_y > 0; --cpt_y)
    {
        // Si la case n'a pas de bonbon et qu'elle peut en recevoir un
        if(!grid->getCell(x,cpt_y)->hasSweet() && grid->isSweetAuthorized(x, cpt_y))
        {
            // Tester si on peut descendre le bonbon en diagonale gauche
            if( (x > 0) && grid->getCell(x-1,cpt_y-1)->hasSweet() && !grid->getCell(x-1,cpt_y-1)->isBlocking())
            {
                // Décaller le bonbon
                grid->swapSweet(x, cpt_y, x - 1, cpt_y - 1);
                notifyObserver(false,x, cpt_y, x - 1, cpt_y - 1);
                return true;
            }
            // Sinon tester si on peut descendre le bonbon en diagonale droite
            else if( (x < (grid->getSizeX() - 1)) && grid->getCell(x+1,cpt_y-1)->hasSweet() && !grid->getCell(x+1,cpt_y-1)->isBlocking())
            {
                // Décaller le bonbon
                grid->swapSweet(x, cpt_y, x + 1, cpt_y - 1);
                notifyObserver(false,x, cpt_y, x + 1, cpt_y - 1);
                return true;
            }
        }
    }

    return false;
}

// Décale tous les bonbons de la grille
void Level::decalage()
{

    // Sur chacune des colonnes
    for(int cpt_x(0); cpt_x < grid->getSizeX(); ++cpt_x)
    {
        do
        {
            // Décaler haut tout ce qu'on peut
            decaler_haut(cpt_x);
            // Afficher
            notifyObserver();
            // Tant qu'on peut générer un bonbon en haut
        } while(grid->generer_bonbon(cpt_x, nb_color));
    }

    int cpt_x_mini, cpt_x_maxi;
    bool decalage_diag(false);
    do
    {
        // Sur chacune des colonnes
        decalage_diag = false;
        for(int cpt_x(0); (cpt_x < grid->getSizeX()) && !decalage_diag; ++cpt_x)
        {
            // Si on a pu décaler par la diagonale
            if(decaler_diagonales(cpt_x))
            {
                // Afficher
                notifyObserver();
                decalage_diag = true;
                // Calculer les bornes
                cpt_x_mini = ((cpt_x - 1)>=0?(cpt_x-1):0);
                cpt_x_maxi = ((cpt_x + 1)<grid->getSizeX()?(cpt_x+1):grid->getSizeX()-1);
                for(; cpt_x_mini <= cpt_x_maxi; ++cpt_x_mini)
                {
                    do
                    {
                        // Décaler haut tout ce qu'on peut
                        decaler_haut(cpt_x_mini);
                        // Afficher
                        notifyObserver();
                        // Tant qu'on peut générer un bonbon en haut
                    } while(grid->generer_bonbon(cpt_x_mini, nb_color));
                }
            }
        }
    } while(decalage_diag);
}

bool Level::decaler_haut(int x)
{
    bool decalage(true), res(false);
    while(decalage)
    {
        decalage = false;
        // Pour chaque case de la colonne
        for(int cpt_y(grid->getSizeY() - 1); cpt_y > 0; --cpt_y)
        {
            // Si la case n'a pas de bonbon et qu'elle peut en recevoir un
            if(!grid->getCell(x,cpt_y)->hasSweet() && grid->isSweetAuthorized(x, cpt_y))
            {
                // Tester si on peut descendre le bonbon au dessus
                if(grid->getCell(x,cpt_y-1)->hasSweet() && !(grid->getCell(x,cpt_y-1)->isBlocking()) )
                {
                    // Décaller le bonbon
                    grid->swapSweet(x, cpt_y, x, cpt_y - 1);
                    notifyObserver(false,x,cpt_y, x, cpt_y-1);
                    decalage = res = true;
                }
            }
        }
    }
    return res;
}

// Renvoie l'état de l'objectif
int Level::etat_objectif() const
{
    // Si la limite de coup est atteinte
    if(hits >= hits_objective)
    {
        // Vérifier l'objectif
        switch(objective)
        {
            // S'il n'y a pas d'autre objectif
            case Level::NONE :
            return (score < score_objective)?OBJECTIVE_FAILURE:OBJECTIVE_SUCCESS;
            break;
            // Si l'objectif est de casser toutes les gélatines
            case Level::GELATINE :
            return ((grid->get_nb_gelatine() > 0) || (score < score_objective))?OBJECTIVE_FAILURE:OBJECTIVE_SUCCESS ;
            break;
            // Si l'objectif est de casser toutes les chantilly
            case Level::CHANTILLY :
            return ((grid->get_nb_chantilly() > 0) || (score < score_objective))?OBJECTIVE_FAILURE:OBJECTIVE_SUCCESS ;
            break;
            // Si l'objectif est de casser toutes les cases
            case Level::CAGE :
            return ((grid->get_nb_cage() > 0) || (score < score_objective))?OBJECTIVE_FAILURE:OBJECTIVE_SUCCESS ;
            break;

            default:
            return OBJECTIVE_REACHABLE;
            break;
        }
    } // END IF LIMITE DE COUP ATTEINTE
    // Sinon s'il y a des coups restants
    else
    {
        // Vérifier si l'objectif a été atteint
        switch(objective)
        {
            // S'il n'y a pas d'autre objectif
            case Level::NONE :
            return (score < score_objective)?OBJECTIVE_REACHABLE:OBJECTIVE_SUCCESS;
            break;
            // Si l'objectif est de casser toutes les gélatines
            case Level::GELATINE :
                // Si toutes les gélatines sont détruites
                if(grid->get_nb_gelatine() == 0)
                {
                    // Si le score n'est pas atteint
                    if(score < score_objective)
                    {
                        return OBJECTIVE_FAILURE;
                    }
                    // Sinon s'il est atteint
                    else
                    {
                        return OBJECTIVE_SUCCESS;
                    }
                }
                // Sinon s'il reste des gélatines à détruire
                else
                {
                    return OBJECTIVE_REACHABLE;
                }
            break;
                // Si l'objectif est de casser toutes les chantilly
            case Level::CHANTILLY :
                // Si toutes les chantilly sont détruites
                if(grid->get_nb_chantilly() == 0)
                {
                    // Si le score n'est pas atteint
                    if(score < score_objective)
                    {
                        return OBJECTIVE_FAILURE;
                    }
                    // Sinon s'il est atteint
                    else
                    {
                        return OBJECTIVE_SUCCESS;
                    }
                }
                // Sinon s'il reste des chantilly à détruire
                else
                {
                    return OBJECTIVE_REACHABLE;
                }
            break;
                // Si l'objectif est de casser toutes les cases
            case Level::CAGE :
                // Si toutes les cages sont détruites
                if(grid->get_nb_cage() == 0)
                {
                    // Si le score n'est pas atteint
                    if(score < score_objective)
                    {
                        return OBJECTIVE_FAILURE;
                    }
                    // Sinon s'il est atteint
                    else
                    {
                        return OBJECTIVE_SUCCESS;
                    }
                }
                // Sinon s'il reste des cages à détruire
                else
                {
                    return OBJECTIVE_REACHABLE;
                }
            break;

            default:
            return OBJECTIVE_REACHABLE;
            break;
        }
    }
}


