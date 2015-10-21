#include "models/grid.h"

using namespace std;


/*
 * Constructeur par défaut
 *
 */

Grid::Grid(int _sizeX, int _sizeY)
    : sizeX(_sizeX), sizeY(_sizeY), nb_gelatine(0), nb_chantilly(0), nb_cage(0)
{
    matrice = new Element**[sizeX];
    for (int x = 0; x < sizeX; x++) {
        matrice[x] = new Element*[sizeY];
        for(int y = 0; y < sizeY; y++)
            matrice[x][y] = NULL;
    }
}

/*
 * Constructeur par recopie
 *
 */

Grid::Grid(const Grid & _grid)
{
    this -> sizeX = _grid.sizeX;
    this -> sizeY = _grid.sizeY;

    this -> nb_gelatine = _grid.nb_gelatine;
    this -> nb_chantilly = _grid.nb_chantilly;
    this -> nb_cage = _grid.nb_cage;

    matrice = new Element**[sizeX];
    for(int x = 0; x < sizeX; x++)
    {
        matrice[x] = new Element*[sizeY];
        for(int y = 0; y < sizeY; y++)
        {
            if(!_grid.matrice[x][y])
            {
                throw MessageError("grid.cpp"
                                   , "Constructor Grid::Grid(const Grid &)"
                                   , "Cell not initialized");
            }
            else
            {
                if(_grid.matrice[x][y] -> playable())
                {
                    matrice[x][y] = new Playable(*((Playable*) _grid.matrice[x][y]));
                }
                else
                {
                    matrice[x][y] = new Obstacle(*((Obstacle*) _grid.matrice[x][y]));
                }
            }
        }
    }
}

/*
 * Destructeur
 *
 */

Grid::~Grid()
{
    if(matrice)
    {
        for (int x = 0; x < sizeX; x++)
        {
            if(matrice[x])
            {
                for(int y = 0; y < sizeY; y++)
                    if(matrice[x][y])
                    {
                        delete matrice[x][y];
                        matrice[x][y] = NULL;
                    }
                delete[] matrice[x];
                matrice[x] = NULL;
            }
        }
        delete[] matrice;
        matrice = NULL;
    }
}

/*
 * Surcharge de l'opérateur d'affectation
 *
 */

Grid & Grid::operator=(const Grid & _grid)
{
    if(this != &_grid)
    {
        if(matrice)
        {
            for (int x = 0; x < sizeX; x++)
            {
                if(matrice[x])
                {
                    for(int y = 0; y < sizeY; y++)
                        if(matrice[x][y])
                            delete matrice[x][y];
                    delete[] matrice[x];
                }
            }
            delete[] matrice;
        }

        this -> sizeX = _grid.sizeX;
        this -> sizeY = _grid.sizeY;

        this -> nb_gelatine = _grid.nb_gelatine;
        this -> nb_chantilly = _grid.nb_chantilly;
        this -> nb_cage = _grid.nb_cage;

        matrice = new Element**[sizeX];
        for(int x = 0; x < sizeX; x++)
        {
            matrice[x] = new Element*[sizeY];
            for(int y = 0; y < sizeY; y++)
            {
                if(!_grid.matrice[x][y])
                {
                    throw MessageError("grid.cpp"
                                       , "Grid & Grid::operator=(const Grid &)"
                                       , "Cell not initialized");
                }
                else
                {
                    if(_grid.matrice[x][y] -> playable())
                    {
                        matrice[x][y] = new Playable(*((Playable*) _grid.matrice[x][y]));
                    }
                    else
                    {
                        matrice[x][y] = new Obstacle(*((Obstacle*) _grid.matrice[x][y]));
                    }
                }
            }
        }
    }

    return *this;
}

/*
 * Accesseurs
 *
 */

int Grid::getSizeX() const
{
    return sizeX;
}
int Grid::getSizeY() const
{
    return sizeY;
}
Element*** Grid::getMatrice()
{
    return matrice;
}
Element* Grid::getCell(int x, int y) const
{
    return (matrice[x][y]);
}

int Grid::get_nb_gelatine()
{
    return nb_gelatine;
}
int Grid::get_nb_chantilly()
{
    return nb_chantilly;
}
int Grid::get_nb_cage()
{
    return nb_cage;
}


/*
 * Fonctions
 *
 */

/*
 * Fonction d'initialisation des bonbons de toute la grille
 */
void Grid::reinitializeAllSweets(int nbColor)
{
    // Parcours de toute la grille
    for(int y = 0; y < sizeY; y++)
        for(int x = 0; x < sizeX; x++)
            // Si la matrice contient un bonbon et n'est pas blocante
            // alors on le réinitialise
            if(matrice[x][y]->hasSweet() && !matrice[x][y]->isBlocking())
            {
                generateSweet(x, y, nbColor);
            }
}


/*
 * Fonction d'initialisation de la grille
 */

void Grid::initialize(int x, int y, int nbColor
                      , bool createObstacle, Difficulty::Name diffName)
{
    if(nbColor < MIN_NB_COLORS_S)
    {
        throw ValueError<int>("grid.cpp"
                              , "void Grid::initialize(int, int, int)"
                              , "Wrong number of used colors. See the minimum value MIN_NB_COLORS_S"
                              , nbColor);
    }
    else if(nbColor > NB_COLORS_S)
    {
        throw ValueError<int>("grid.cpp"
                              , "void Grid::initialize(int, int, int)"
                              , "Wrong number of used colors. See the maximum value NB_COLORS_S"
                              , nbColor);
    }
    else
    {
        // Si la case est vide, l'initialiser par défaut
        if(!matrice[x][y])
        {
            /*
             * D'abord vérifier si c'est un obstacle
             */
            if(createObstacle)
            {
                matrice[x][y] = new Obstacle();
            }
            /*
             * Sinon vérifier si la case à créer comporte une difficulté
             * Sans initialiser le bonbon (à faire après)
             */
            else if(diffName != Difficulty::NONE)
            {
                matrice[x][y] = new Playable(diffName);
                // Mettre à jour les compteurs de cases spéciales
                switch(diffName)
                {
                    case Difficulty::GEL_1 :
                        ++nb_gelatine;
                    break;
                    case Difficulty::GEL_2 :
                        ++nb_gelatine;
                    break;
                    case Difficulty::CHANTILLY :
                        ++nb_chantilly;
                    break;
                    case Difficulty::CAGE :
                        ++nb_cage;
                    break;
                    default:
                    break;
                }
            }
            /*
             * Sinon on créé une case playable sans difficulté
             * avec un bonbon initialisé
             */
            else
            {
                matrice[x][y] = new Playable();
                generateSweet(x, y,nbColor);
            }
        }
        // Sinon si la case est de type playable
        else if(matrice[x][y] -> playable())
        {
            if(((Playable*) matrice[x][y]) -> getDifficulty().isSweetPresence())
            {
                generateSweet(x, y,nbColor);
            }
        }
        // Sinon la case est de type Obstacle, ne rien faire
        else {}
    }
}

/*
 * Choix du bonbon à mettre dans la grille
 *
 */
void Grid::generateSweet(int x, int y, int nbColor, bool naive)
{
    Sweet* aux;
    if(isSweetAuthorized(x, y))
    {
        int sweet_t[nbColor];
        int ind_aux;
        Sweet::Color firstCell, secondCell;

        // Initialisationdu tableau de couleurs
        for(int i = 0; i < nbColor; i++)
            sweet_t[i] = i + 1;

        if(!naive)
        {

            // Si on est au moins à la 3e colonne
            if(x >= THIRD_COLUMN)
            {
                // Si les deux cases à gauche sont jouable
                if(matrice[x - 1][y] -> playable()
                   && matrice[x - 2][y] -> playable())
                {
                    // Si la case précédente contient un bonbon
                    if(((Playable*) matrice[x - 1][y]) -> getSweet()
                       && ((Playable*) matrice[x - 2][y]) -> getSweet())
                    {
                        firstCell = ((Playable*)matrice[x - 1][y]) -> getSweet() -> getColor();
                        secondCell = ((Playable*)matrice[x - 2][y]) -> getSweet() -> getColor();
                        // Si ces deux cases sont identiques ET Color != NONE
                        if(firstCell == secondCell
                           && firstCell != Sweet::NONE && secondCell != Sweet::NONE)
                        {
                            // Permuter avec l'élément à l'indice 'nbColor'
                            ind_aux = findIn(sweet_t, nbColor, (int)firstCell);
                            nbColor--;
                            permute(sweet_t, ind_aux, nbColor);
                        }
                    }
                }
            }

            // Si on est au moins à la 3e ligne
            if(y >= THIRD_LINE)
            {
                // Si les deux cases au dessus sont jouables
                if(matrice[x][y - 1] -> playable()
                   && matrice[x][y - 2] -> playable())
                {
                    // Si la case précédente contient un bonbon
                    if(((Playable*) matrice[x][y - 1]) -> getSweet()
                       && ((Playable*) matrice[x][y - 2]) -> getSweet())
                    {
                        firstCell = ((Playable*)matrice[x][y - 1]) -> getSweet() -> getColor();
                        secondCell = ((Playable*)matrice[x][y - 2]) -> getSweet() -> getColor();
                        // Si ces deux cases sont identiques ET Color != NONE
                        if(firstCell == secondCell
                           && firstCell != Sweet::NONE && secondCell != Sweet::NONE)
                        {
                            // Rechercher l'indice de la couleur
                            ind_aux = findIn(sweet_t, nbColor, (int)firstCell);
                            // Si l'indice est < à nbColor
                            if(ind_aux != NOT_FOUND)
                            {
                                // Permuter avec l'élément à l'indice 'nbColor'
                                nbColor--;
                                permute(sweet_t, ind_aux, nbColor);
                            }
                        }
                    }
                }
            }
        }
        aux = new Sweet((Sweet::Color)sweet_t[randomInt(0, nbColor)]);
        ((Playable*) matrice[x][y]) -> setSweet(*aux);
        delete aux;
    }
}

bool Grid::isSweetAuthorized(int x, int y)
{
    // Si on est après la première ligne
    if( matrice[x][y] -> isBlocking()
        && !((Playable*)matrice[x][y])->getDifficulty().isSweetPresence() )
    {
        return false;
    }
    else if(y > 0)
    {
        // Si la case au dessus est blocante (ou pas de bonbon), on vérifie celle de gauche et droite
        if( ( matrice[x][y - 1] -> isBlocking()
              && !((Playable*)matrice[x][y])->getDifficulty().isSweetPresence() )
            || !(matrice[x][y - 1] -> hasSweet()))
        {
            if(x == 0)
            {
                if(matrice[x + 1][y - 1] -> isBlocking()
                   || !(matrice[x + 1][y - 1] -> hasSweet()))
                {
                    return false;
                }
            }
            else if(x == sizeX - 1)
            {
                if(matrice[x - 1][y - 1] -> isBlocking()
                   || !(matrice[x - 1][y - 1] -> hasSweet()))
                {
                    return false;
                }
            }
            else
            {
                if((matrice[x - 1][y - 1] -> isBlocking()
                    || !(matrice[x - 1][y - 1] -> hasSweet()))
                   && (matrice[x + 1][y - 1] -> isBlocking()
                       || !(matrice[x + 1][y - 1] -> hasSweet())))
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Grid::coup_possible()
{
    bool res(false);

    // Parcours de toute la grille ligne par ligne
    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++)
        {
            // S'il y a un bonbon dans la case parcourue
            if(matrice[x][y]->hasSweet())
            {
                // Cas où il reste au moins 1 bonbon à droite de la case parcourue
                if(x < sizeX - 1 && matrice[x + 1][y]->hasSweet())
                {
                    // Cas où il reste au moins 2 bonbon à droite de la case parcourue
                    if(x < sizeX - 2 && matrice[x + 2][y]->hasSweet())
                    {
                        // Cas où deux bonbons de même couleur sont séparés par
                        // un bonbon d'une autre couleur à droite de la case parcourue
                        // et que la case entre ces deux bonbons n'est pas blocante
                        if(((Playable*)matrice[x][y])->getSweet()->getColor()
                           == ((Playable*)matrice[x + 2][y])->getSweet()->getColor()
                           && !matrice[x + 1][y]->isBlocking())
                        {
                            // Liste des cas à traiter
                            if(y > 0 && matrice[x + 1][y - 1] -> hasSweet() && !matrice[x + 1][y - 1]->isBlocking()
                               && ((Playable*)matrice[x][y])->getSweet()->getColor()
                               == ((Playable*)matrice[x + 1][y - 1])->getSweet()->getColor())
                                res = true;
                            else if(y < sizeY - 1 && matrice[x + 1][y + 1] -> hasSweet() && !matrice[x + 1][y + 1]->isBlocking()
                                    && ((Playable*)matrice[x][y])->getSweet()->getColor()
                                    == ((Playable*)matrice[x + 1][y + 1])->getSweet()->getColor())
                                res = true;
                        }
                    }

                    // Cas où deux bonbons de même couleur sont côte à côte
                    // à droite de la case parcourue
                    if(((Playable*)matrice[x][y])->getSweet()->getColor()
                       == ((Playable*)matrice[x + 1][y])->getSweet()->getColor())
                    {
                        // Si on est au moins plus loin que la première colonne
                        // et que la case à gauche de la case parcourue n'est pas blocante
                        if(x > 0 && !matrice[x - 1][y]->isBlocking())
                        {
                            if(x > 1 && matrice[x - 2][y] -> hasSweet() && !matrice[x - 2][y]->isBlocking()
                               && ((Playable*)matrice[x][y])->getSweet()->getColor()
                               == ((Playable*)matrice[x - 2][y])->getSweet()->getColor())
                                res = true;
                            else if(y > 0 && matrice[x - 1][y - 1] -> hasSweet()  && !matrice[x - 1][y - 1]->isBlocking()
                                    && ((Playable*)matrice[x][y])->getSweet()->getColor()
                                    == ((Playable*)matrice[x - 1][y - 1])->getSweet()->getColor())
                                res = true;
                            else if(y < sizeY - 1 && matrice[x - 1][y + 1] -> hasSweet() && !matrice[x - 1][y + 1]->isBlocking()
                                    && ((Playable*)matrice[x][y])->getSweet()->getColor()
                                    == ((Playable*)matrice[x - 1][y + 1])->getSweet()->getColor())
                                res = true;
                        }
                        // Sinon si on est avant l'avant derniere colonne de la grille
                        // et que la case située deux cases a droite de la case parcourue n'est pas blocante
                        else if(x < sizeX - 2 && !matrice[x + 2][y]->isBlocking())
                        {
                            if(x < sizeX - 3 && matrice[x + 3][y] -> hasSweet() && !matrice[x + 3][y]->isBlocking()
                               && ((Playable*)matrice[x][y])->getSweet()->getColor()
                               == ((Playable*)matrice[x + 3][y])->getSweet()->getColor())
                                res = true;
                            else if(y > 0 && matrice[x + 2][y - 1] -> hasSweet() && !matrice[x + 2][y - 1]->isBlocking()
                                    && ((Playable*)matrice[x][y])->getSweet()->getColor()
                                    == ((Playable*)matrice[x + 2][y - 1])->getSweet()->getColor())
                                res = true;
                            else if(y < sizeY - 1 && matrice[x + 2][y + 1] -> hasSweet() && !matrice[x + 2][y + 1]->isBlocking()
                                    && ((Playable*)matrice[x][y])->getSweet()->getColor()
                                    == ((Playable*)matrice[x + 2][y + 1])->getSweet()->getColor())
                                res = true;
                        }
                    }
                }

                // Cas où il reste au moins 1 bonbon en dessous de la case parcourue
                if(y < sizeY - 1 && matrice[x][y + 1]->hasSweet())
                {
                    // Cas où il reste au moins 2 bonbon en dessous de la case parcourue
                    if(y < sizeY - 2 && matrice[x][y + 2]->hasSweet())
                    {
                        // Cas où deux bonbons de même couleur sont séparés par
                        // un bonbon d'une autre couleur en dessous de la case parcourue
                        if(((Playable*)matrice[x][y])->getSweet()->getColor()
                           == ((Playable*)matrice[x][y + 2])->getSweet()->getColor()
                           && !matrice[x][y + 1]->isBlocking())
                        {
                            // Liste des cas à traiter
                            if(x > 0 && matrice[x - 1][y + 1] -> hasSweet() && !matrice[x - 1][y + 1]->isBlocking()
                               && ((Playable*)matrice[x][y])->getSweet()->getColor()
                               == ((Playable*)matrice[x - 1][y + 1])->getSweet()->getColor())
                                res = true;
                            else if(x < sizeX - 1 && matrice[x + 1][y + 1] -> hasSweet() && !matrice[x + 1][y + 1]->isBlocking()
                                    && ((Playable*)matrice[x][y])->getSweet()->getColor()
                                    == ((Playable*)matrice[x + 1][y + 1])->getSweet()->getColor())
                                res = true;
                        }
                    }

                    // Cas où deux bonbons de même couleur sont côte à côte
                    // en dessous de la case parcourue
                    if(((Playable*)matrice[x][y])->getSweet()->getColor()
                       == ((Playable*)matrice[x][y + 1])->getSweet()->getColor())
                    {
                        // Sinon si on est au dessus de la derniere ligne de la grille
                        // et que la case située deux cases au dessous de la case parcourue n'est pas blocante
                        if(y > 0 && !matrice[x][y - 1]->isBlocking())
                        {
                            if(y > 1 && matrice[x][y - 2] -> hasSweet() && !matrice[x][y - 2]->isBlocking()
                               && ((Playable*)matrice[x][y])->getSweet()->getColor()
                               == ((Playable*)matrice[x][y- 2])->getSweet()->getColor())
                                res = true;
                            else if(x > 0 && matrice[x - 1][y - 1] -> hasSweet() && !matrice[x - 1][y - 1]->isBlocking()
                                    && ((Playable*)matrice[x][y])->getSweet()->getColor()
                                    == ((Playable*)matrice[x - 1][y - 1])->getSweet()->getColor())
                                res = true;
                            else if(x < sizeX - 1 && matrice[x + 1][y - 1] -> hasSweet() && !matrice[x + 1][y - 1]->isBlocking()
                                    && ((Playable*)matrice[x][y])->getSweet()->getColor()
                                    == ((Playable*)matrice[x + 1][y - 1])->getSweet()->getColor())
                                res = true;
                        }

                        // Sinon si on est avant l'avant derniere ligne de la grille
                        // et que la case située deux cases au dessous de la case parcourue n'est pas blocante
                        else if(y < sizeY - 2 && !matrice[x][y + 2]->isBlocking())
                        {
                            if(y < sizeY - 3 && matrice[x][y + 3] -> hasSweet() && !matrice[x][y + 3]->isBlocking()
                               && ((Playable*)matrice[x][y])->getSweet()->getColor()
                               == ((Playable*)matrice[x][y + 3])->getSweet()->getColor())
                                res = true;
                            else if(x > 0 && matrice[x - 1][y + 2] -> hasSweet() && !matrice[x - 1][y + 2]->isBlocking()
                                    && ((Playable*)matrice[x][y])->getSweet()->getColor()
                                    == ((Playable*)matrice[x - 1][y + 2])->getSweet()->getColor())
                                res = true;
                            else if(x < sizeX - 1 && matrice[x + 1][y + 2] -> hasSweet() && !matrice[x + 1][y + 2]->isBlocking()
                                    && ((Playable*)matrice[x][y])->getSweet()->getColor()
                                    == ((Playable*)matrice[x + 1][y + 2])->getSweet()->getColor())
                                res = true;
                        }
                    }
                }
            }
        } // END for x
    } // END for y

    return res;
}

// Détruit une case
void Grid::burst(int x, int y)
{
    // Détruire le bonbon
    ((Playable*)matrice[x][y])->deleteSweet();
    // Change la difficulté
    changeDifficulty(x,y);
}

// Modifie la difficulté de la case (x,y)
void Grid::changeDifficulty(int x,int y)
{
    // Récupérer la difficulté actuelle de la case
    Difficulty diff_aux  = ((Playable*)matrice[x][y])->getDifficulty();
    // Mettre à jour les compteurs de cases spéciales
    switch(diff_aux.getName())
    {
        case Difficulty::GEL_1 :
            --nb_gelatine;
        break;
        case Difficulty::CHANTILLY :
            --nb_chantilly;
        break;
        case Difficulty::CAGE :
            --nb_cage;
        break;
        default:
        break;
    }
    // Modifier la difficulté de la case
    ((Playable*)matrice[x][y])->setDifficulty(((Playable*)matrice[x][y])->getDifficulty().change());
}

// Permutte deux cases entre elles
void Grid::swapSweet(int x1, int y1, int x2, int y2)
{
    Sweet *aux;
    aux = ((Playable*)matrice[x1][y1])->getSweet();
    ((Playable*)matrice[x1][y1])->setSweet(((Playable*)matrice[x2][y2])->getSweet());
    ((Playable*)matrice[x2][y2])->setSweet(aux);
}

// Génère un bonbon en haut de la colonne
bool Grid::generer_bonbon(int x, int nb_color)
{
    // Si la case est valide
    if(!matrice[x][0]->hasSweet() && !matrice[x][0]->isBlocking())
    {
        // Générer un bonbon
        generateSweet(x, 0, nb_color, true);
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& out, const Grid& grid)
{
    for(int y = 0; y < grid.sizeY; y++)
    {
        for(int x = 0; x < grid.sizeX; x++)
        {
            if(grid.matrice[x][y] -> playable())
            {
                if(grid.matrice[x][y] -> hasSweet())
                    out << (int)(((Playable*)grid.matrice[x][y]) -> getSweet() -> getColor()) << " ";
                else
                    out << "X ";
            }
            else out << "M ";
        }
        out << endl;
    }

    out << endl;

    for(int y = 0; y < grid.sizeY; y++)
    {
        for(int x = 0; x < grid.sizeX; x++)
        {
            if(grid.matrice[x][y] -> playable())
                out << "1";
            else
                out << "0";
            out << " ";
        }
        out << endl;
    }

    return out;
}
