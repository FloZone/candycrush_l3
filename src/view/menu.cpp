#include <iostream>
#include <dirent.h>
#include <regex>

#include "view/menu.h"

using namespace std;

#define HAUTEUR_MENU 800
#define LARGEUR_MENU 800

#define MARGE_GAUCHE_LISTE 340


Menu::Menu()
    : MainWindow("Sweet Crash", LARGEUR_MENU, HAUTEUR_MENU), nb_niveaux(0)
{
    // Charger la police
    if (!font.loadFromFile("./ressources/mytype.ttf"))
    {
        throw MessageError("menu.cpp"
                           ,"Constructor Menu::Menu())"
                           ,"Unable to load \"./ressources/mytype.ttf\"." );
    }

    if (!fond.loadFromFile("./ressources/arriere_plan.png"))
        throw ValueError<string>("menu.cpp"
                                 , "Constructor Menu::Menu()"
                                 , "Unable to open following file"
                                 , "./ressources/arriere_plan.png");

    image_fond.setTexture(fond);
    image_fond.setScale(((float)vMode->width) / ((float)image_fond.getTexture()->getSize().x)
                        , ((float)vMode->height) / ((float)image_fond.getTexture()->getSize().y));

    if (!titre_jeu.loadFromFile("./ressources/titre_menu.png"))
        throw ValueError<string>("menu.cpp"
                                 , "Constructor Menu::Menu()"
                                 , "Unable to open following file"
                                 , "./ressources/titre_menu.png");

    titre.setTexture(titre_jeu);
    titre.setPosition(0,20);
    titre.setScale(((float)vMode->width) / ((float)titre.getTexture()->getSize().x)
                   , ((float)vMode->width) / ((float)titre.getTexture()->getSize().x));

    if (!liste_niveaux.loadFromFile("./ressources/liste_level.png"))
        throw ValueError<string>("menu.cpp"
                                 , "Constructor Menu::Menu()"
                                 , "Unable to open following file"
                                 , "./ressources/liste_level.png");

    liste.setTexture(liste_niveaux);
    liste.setScale(((float)vMode->width) / ((float)liste.getTexture()->getSize().x)
                   , ((float)vMode->width) / ((float)liste.getTexture()->getSize().x));
    liste.setPosition(0,((float)vMode->width) / ((float)titre.getTexture()->getSize().x)*titre.getTexture()->getSize().y + 30);

    if (!bouton_level.loadFromFile("./ressources/bouton_level.png"))
        throw ValueError<string>("menu.cpp"
                                 , "Constructor Menu::Menu()"
                                 , "Unable to open following file"
                                 , "./ressources/bouton_level.png");

    level.setTexture(bouton_level);
    level.setScale(0.6,0.6);


    // Lister les niveaux
    struct dirent *lecture;
    regex e ("(.*)(.yml)");
    DIR *dossier;

    dossier = opendir("./levels/");
    if(dossier == NULL)
    {
        throw MessageError("mainwindow.cpp"
                           ,"Constructor MainWindow::MainWindow(string, int, int)"
                           ,"Unable to open \"./levels/ directory\"." );
    }

    // Compter le nombre de niveaux
    while((lecture = readdir(dossier)))
    {
        if (std::regex_match(lecture->d_name,e))
        {
            ++nb_niveaux;
        }
    }
    closedir(dossier);

    niveaux = new sf::Text[nb_niveaux];

    dossier = opendir("./levels/");
    if(dossier == NULL)
    {
        throw MessageError("mainwindow.cpp"
                           ,"Constructor MainWindow::MainWindow(string, int, int)"
                           ,"Unable to open \"./levels/ directory\"." );
    }
    int cpt_niveaux(0);
    std::string aux;
    // Stocker les niveaux
    while((lecture = readdir(dossier)))
    {
        if (std::regex_match(lecture->d_name,e))
        {
            aux = lecture->d_name;
            aux = aux.substr(0, aux.length()-4);

            niveaux[cpt_niveaux].setString(aux);
            niveaux[cpt_niveaux].setPosition(MARGE_GAUCHE_LISTE, ((float)vMode->width) / ((float)titre.getTexture()->getSize().x)*titre.getTexture()->getSize().y +
                                             (float)liste.getTexture()->getSize().y +(0.6*cpt_niveaux*level.getTexture()->getSize().y));
            niveaux[cpt_niveaux].setFont(font);
            niveaux[cpt_niveaux].setColor(sf::Color::Black);
            niveaux[cpt_niveaux].setCharacterSize(20);

            ++cpt_niveaux;
        }
    }
    closedir(dossier);

}

// Coplien
Menu::Menu(const Menu & menu)
    : MainWindow("Sweet Crash", LARGEUR_MENU, HAUTEUR_MENU), nb_niveaux(0)
{
    this -> nb_niveaux = menu.nb_niveaux;
    niveaux = new sf::Text[nb_niveaux];
    for(unsigned int cpt(0); cpt < nb_niveaux; ++cpt)
    {
        niveaux[cpt].setString(menu.niveaux[cpt].getString());
    }
}
Menu & Menu::operator=(const Menu & menu)
{
    if(this != & menu)
    {
        if(niveaux)
        {
            delete niveaux;
        }
        this -> nb_niveaux = menu.nb_niveaux;
        niveaux = new sf::Text[nb_niveaux];
        for(unsigned int cpt(0); cpt < nb_niveaux; ++cpt)
        {
            niveaux[cpt].setString(menu.niveaux[cpt].getString());
        }
    }
    return *this;
}
Menu::~Menu()
{
    if(niveaux)
        delete niveaux;
}

/*
 * Fonctions
 */
void Menu::affichage()
{
    window->clear();
    window->draw(image_fond);
    window->draw(titre);
    window->draw(liste);
    afficher_liste();
    window->display();
}

string Menu::listenAndDraw()
{

    bool clic(false);
    int clic_x(0), clic_y(0);
    string res;
    // Tant que la fenêtre est ouverte
    while(window->isOpen())
    {
        // Détecter les évennements
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
                // Fermer la fenêtre
                case sf::Event::Closed:
                    window->close();
                break;

                    // Clic relaché
                case sf::Event::MouseButtonReleased:
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        clic = true;
                        clic_x = event.mouseButton.x;
                        clic_y = event.mouseButton.y;
                    }
                break;


                default: break;
            } // END OF SWITCH EVENT TYPE
        } // END OF WHILE EVENT

        // Si le joueur a cliqué
        if(clic)
        {
            clic = false;
            // Récupérer le niveau choisi
            res = charger_niveau(clic_x, clic_y);
            if(res != "null")
            {
                window->close();
                return "./levels/" + res + ".yml";
            }
        }

        affichage();

    } // END WHILE IS OPEN

    return "exit";
}

// Affiche la liste des niveaux du dossier
void Menu::afficher_liste()
{
    sf::FloatRect textRect;
    for(unsigned int cpt(0); cpt < nb_niveaux; ++cpt)
    {
        level.setPosition(MARGE_GAUCHE_LISTE - level.getTexture()->getSize().x/7, ((float)vMode->width) / ((float)titre.getTexture()->getSize().x)*titre.getTexture()->getSize().y +
                          (float)liste.getTexture()->getSize().y +(0.6*cpt*level.getTexture()->getSize().y) - level.getTexture()->getSize().y/6);
        window->draw(level);

        window->draw(niveaux[cpt]);
    }
}

// Renvoi le nom du niveau sur lequel le joueur a cliqué
string Menu::charger_niveau(unsigned int clic_x, unsigned int clic_y)
{
    // Si après les boutons sur y
    unsigned int indice = ((clic_y - ((float)vMode->height) / ((float)titre.getTexture()->getSize().x)*titre.getTexture()->getSize().y + (float)liste.getTexture()->getSize().y +(0.6*level.getTexture()->getSize().y) - level.getTexture()->getSize().y/6) / (0.6*level.getTexture()->getSize().y))-6 ;
    if( indice >= nb_niveaux )
        return "null";

    // Si avant ou après les boutons sur x
    else if( clic_x < (MARGE_GAUCHE_LISTE - level.getTexture()->getSize().x/7)
             || clic_x > (MARGE_GAUCHE_LISTE - level.getTexture()->getSize().x/7 + 0.6*level.getTexture()->getSize().x) )
        return "null";

    // Si avant les boutons sur y
    else if( clic_y < ((float)vMode->width) / ((float)titre.getTexture()->getSize().x)*titre.getTexture()->getSize().y + (float)liste.getTexture()->getSize().y - level.getTexture()->getSize().y/6 )
        return "null";

    // Le clic est valide, charger le niveau
    return niveaux[indice].getString();

}


// Implémentation d'Observer
void Menu::notifyObservable(int,int,int,int)
{

}
void Menu::update(const Level &)
{

}
void Menu::update(const Level &,bool,bool,int,int,int,int)
{

}
