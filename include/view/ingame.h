#ifndef INGAME_H
#define INGAME_H

#include <cstdio>

#include "mainwindow.h"

#define TAILLE_MAX 9

class InGame : public MainWindow
{
public:
    InGame(const Level &level);
    ~InGame();


    int listenAndDraw(const Level &);

   // Implémentation d'Observable
    void notifyObservable(bool drag, int x1, int y1, int x2, int y2);
    void update(const Level &);
    void update(const Level &,bool,bool,int,int,int,int);

private:
    sf::Texture fond;
    sf::Sprite image_fond;
    sf::Texture texture;

    sf::Texture bonbon_rouge;
    sf::Sprite rouge;

    sf::Texture bonbon_orange;
    sf::Sprite orange;

    sf::Texture bonbon_vert;
    sf::Sprite vert;

    sf::Texture bonbon_violet;
    sf::Sprite violet;

    sf::Texture bonbon_jaune;
    sf::Sprite jaune;

    sf::Texture bonbon_bleu;
    sf::Sprite bleu;

    sf::Texture case_cage;
    sf::Sprite cage;

    sf::Texture case_gelatine;
    sf::Sprite gelatine;

    sf::Texture case_gelatine2;
    sf::Sprite gelatine2;

    sf::Texture case_chantilly;
    sf::Sprite chantilly;

    sf::Texture case_mur;
    sf::Sprite mur;

    sf::Texture case_stat;
    sf::Sprite stat;

    sf::Texture ecran_fin_partie;
    sf::Sprite fin_partie;

    sf::Texture bonbon_vide;
    sf::Sprite deplacer_bonbon_1;
    sf::Sprite deplacer_bonbon_2;

    sf::Texture ecran_victoire;
    sf::Sprite victoire;

    sf::Texture ecran_defaite;
    sf::Sprite defaite;

    sf::Texture bouton_rejouer;
    sf::Sprite rejouer;

    sf::Texture bouton_retour_menu;
    sf::Sprite retour_menu;

    sf::Texture fond_noir_bonbon;
    sf::Sprite fond_bonbon;

    sf::Texture arriere_plan_bonbon;
    sf::Sprite arriere_bonbon;

    sf::Sprite arriere_plan;

    sf::Font font_variable;
    sf::Font font_text;

    sf::Text score_value;
    sf::Text sco_objectif_value;
    sf::Text deplacement_value;
    sf::Text objectif_value;

    void affichage(const Level &,bool,bool,int,int,int,int);
    void affichage_fin(bool);
    void load_sprite(const Level&,int,int, int, int);
    void masquer_case(const Level&, int, int, int, int, bool[TAILLE_MAX][TAILLE_MAX]);
    void move_sweet(const Grid &,int,int,int,int);
    int calculer_direction(int,int,int,int);
    bool clic_hors_grille(const Grid &,unsigned int,unsigned int,unsigned int,unsigned int);
    void effectuer_mouvement(const Grid &,int,int,int,int);
    int clic_fin_niveau(unsigned int clic_x, unsigned int clic_y);
};

#endif // INGAME_H
