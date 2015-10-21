#include <iostream>
#include <ctime>
#include <SFML/Window.hpp>

#include "util/util.h"
#include "models/level.h"
#include "models/grid.h"

#include "view/mainwindow.h"
#include "view/ingame.h"
#include "view/menu.h"

using namespace std;

#define CLIC_EXIT 0
#define CLIC_MENU 1
#define CLIC_REPLAY 2


int main()
{
    srand(time(NULL));

    try
    {

        int choix;
        do {
            Menu menu;
            string level_name(menu.listenAndDraw());

            // Si le joueur ferme le jeu
            if(level_name == "exit")
                return 0;

            do
            {
                // Charger le niveau
                Level * level = new Level(level_name);
                InGame w(*level);
                // Mettre en place le MVC
                level->addObserver(&w);
                w.addObservable(level);

                // Lancer le jeu
                choix = w.listenAndDraw(*level);

                // Détruire le niveau
                delete level;

            } while(choix == CLIC_REPLAY);
        } while(choix == CLIC_MENU || choix == CLIC_EXIT);

        /*
         * Mettre ici absolument tout le code que l'on veut rajouter dans le main.cpp
         * meme si c'est pour tester
         * ATTENTION : Ne rien changer d'autre dans la fonction int main() !!
         */
    }
    catch(const exception & e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}
