#ifndef MENU_H
#define MENU_H

#include "mainwindow.h"


class Menu : public MainWindow
{
public:
    Menu();
    Menu(const Menu &);
    Menu & operator=(const Menu &);
    ~Menu();

    std::string listenAndDraw();

    /* Implémentation d'Observable */
    void notifyObservable(int,int,int,int);
    void update(const Level &);
    void update(const Level &,bool,bool,int,int,int,int);

private:

    void afficher_liste();
    std::string charger_niveau(unsigned int, unsigned int);
    void affichage();

    unsigned int nb_niveaux;
    sf::Text * niveaux;

    sf::Font font;

    sf::Texture titre_jeu;
    sf::Sprite titre;

    sf::Texture liste_niveaux;
    sf::Sprite liste;

    sf::Texture fond;
    sf::Sprite image_fond;

    sf::Texture bouton_level;
    sf::Sprite level;

};

#endif // MENU_H
