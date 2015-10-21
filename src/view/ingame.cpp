#include <iostream>
#include <SFML/System/Time.hpp>
#include "view/ingame.h"

using namespace std;

#define DIR_NULL -1
#define DIR_HAUT 0
#define DIR_BAS 1
#define DIR_DROITE 2
#define DIR_GAUCHE 3
#define TAILLE 88

#define CLIC_NULL -1
#define CLIC_EXIT 0
#define CLIC_MENU 1
#define CLIC_REPLAY 2

#define TAILLE_MAX 9

InGame::InGame(const Level &level)
    : MainWindow("My Window", 840, (level.getGrid()->getSizeY()+2)*TAILLE)
{

    window->setTitle(level.getName());

    if (!fond.loadFromFile("./ressources/arriere_plan.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/arriere_plan.png");

    image_fond.setTexture(fond);
    image_fond.setScale(((float)vMode->width) / ((float)image_fond.getTexture()->getSize().x)
                        , ((float)vMode->height) / ((float)image_fond.getTexture()->getSize().y));

    if (!fond_noir_bonbon.loadFromFile("./ressources/fond_noir_2_bonbon.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/fond_noir_2_bonbon.png");

    fond_bonbon.setTexture(fond_noir_bonbon);
    fond_bonbon.setScale(0.89f,0.89f);

    if (!arriere_plan_bonbon.loadFromFile("./ressources/arriere_plan_bonbon.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/arriere_plan_bonbon.png");

    arriere_bonbon.setTexture(arriere_plan_bonbon);
    arriere_bonbon.setScale(0.89f,0.89f);



    if (!texture.loadFromFile("./ressources/fond_noir_2.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/fond_noir_2.png");




    //Creation texture bonbon rouge
    if (!bonbon_rouge.loadFromFile("./ressources/bonbon_rouge2.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/bonbon_rouge2.png");

    rouge.setTexture(bonbon_rouge);
    rouge.setScale(0.87f,0.87f);

    //Creation texture bonbon orange
    if (!bonbon_orange.loadFromFile("./ressources/bonbon_orange2.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/bonbon_orange2.png");

    orange.setTexture(bonbon_orange);
    orange.setScale(0.87f,0.87f);
    //Creation texture bonbon vert
    if (!bonbon_vert.loadFromFile("./ressources/bonbon_vert2.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/bonbon_vert2.png");

    vert.setTexture(bonbon_vert);
    vert.setScale(0.87f,0.87f);

    //Creation texture bonbon violet
    if (!bonbon_violet.loadFromFile("./ressources/bonbon_violet2.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/bonbon_violet2.png");

    violet.setTexture(bonbon_violet);
    violet.setScale(0.87f,0.87f);

    //Creation texture bonbon jaune
    if (!bonbon_jaune.loadFromFile("./ressources/bonbon_jaune2.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/bonbon_jaune2.png");

    jaune.setTexture(bonbon_jaune);
    jaune.setScale(0.87f,0.87f);

    //Creation texture bonbon bleu
    if (!bonbon_bleu.loadFromFile("./ressources/bonbon_bleu2.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/bonbon_bleu2.png");

    bleu.setTexture(bonbon_bleu);
    bleu.setScale(0.87f,0.87f);

    //Creation texture bonbon vide
    if (!bonbon_vide.loadFromFile("./ressources/bonbon_vide.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/bonbon_vide.png");


    //Creation texture cage
    if (!case_cage.loadFromFile("./ressources/cage.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/cage.png");

    cage.setTexture(case_cage);

    // Creation de la texture gelatine_1
    if (!case_gelatine.loadFromFile("./ressources/gelatine.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/gelatine.png");

    gelatine.setTexture(case_gelatine);
    gelatine.setScale(1.0f,1.16f);
    gelatine.setColor(sf::Color(255,255,255,200));


    // Creation de la texture gelatine_2
    if (!case_gelatine2.loadFromFile("./ressources/gelatine2.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/gelatine2.png");

    gelatine2.setTexture(case_gelatine2);
    gelatine2.setScale(1.0f,1.16f);

    // Creation de la texture chantilly
    if (!case_chantilly.loadFromFile("./ressources/chantilly.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/chantilly.png");

    chantilly.setTexture(case_chantilly);

    // Creation de la texture mur
    if (!case_mur.loadFromFile("./ressources/mur_1.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/mur_1.png");

    mur.setTexture(case_mur);

    // Creation de la texture objectif
    if (!ecran_fin_partie.loadFromFile("./ressources/arriere_plan.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/arriere_plan.png");


    fin_partie.setTexture(ecran_fin_partie);
    fin_partie.setScale(0.4,0.48);
    fin_partie.setColor(sf::Color(254,249,160,240));
    fin_partie.setPosition(vMode->width/2 - 0.4*ecran_fin_partie.getSize().x/2,TAILLE*2.1);


    // Creation de la texture objectif
    if (!ecran_defaite.loadFromFile("./ressources/echec_niveau.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/echec_niveau.png");


    defaite.setTexture(ecran_defaite);
    defaite.setScale(0.5,0.5);
    defaite.setPosition(vMode->width/2 - 0.5*ecran_defaite.getSize().x/2, TAILLE*3);

    // Creation de la texture victoire
    if (!ecran_victoire.loadFromFile("./ressources/niveau_reussit.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/niveau_reussit.png");


    victoire.setTexture(ecran_victoire);
    victoire.setScale(0.5,0.5);
    victoire.setPosition(vMode->width/2 - 0.5*ecran_victoire.getSize().x/2, TAILLE*3);


    // Creation de la texture du bouton rejouer
    if (!bouton_rejouer.loadFromFile("./ressources/recommencer.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/recommencer.png");

    rejouer.setTexture(bouton_rejouer);
    rejouer.setScale(0.5,0.5);
    rejouer.setPosition(vMode->width/2 - 0.5*bouton_rejouer.getSize().x/2, TAILLE*5.2);
    // Creation de la texture du bouton retour menu
    if (!bouton_retour_menu.loadFromFile("./ressources/retour_menu.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/retour_menu.png");

    retour_menu.setTexture(bouton_retour_menu);
    retour_menu.setScale(0.5,0.5);
    retour_menu.setPosition(vMode->width/2 - 0.5*bouton_rejouer.getSize().x/2, TAILLE*6);


    // Creation de la texture stat
    if (!case_stat.loadFromFile("./ressources/texture_button.png"))
        throw ValueError<string>("ingame.cpp"
                                 , "Constructor InGame::InGame(const Grid &)"
                                 , "Unable to open following file"
                                 , "./ressources/texture_button.png");

    stat.setTexture(case_stat);
    stat.setScale((float)(vMode->width)/(float)(case_stat.getSize().x),0.5f);
    stat.setPosition(0, TAILLE/2);
    //stat.setScale((float)(case_stat.getSize().x/vMode->width),(float)(case_stat.getSize().x/vMode->width));

    if (!font_variable.loadFromFile("./ressources/GretoonHighlight.ttf"))
    {
        throw MessageError("ingame.cpp"
                           ,"Constructor InGame::InGame(const Level &)"
                           ,"Unable to load \"./ressources/GretoonHighlight.ttf\"." );
    }
    if (!font_text.loadFromFile("./ressources/mytype.ttf"))
    {
        throw MessageError("ingame.cpp"
                           ,"Constructor InGame::InGame(const Level &)"
                           ,"Unable to load \"./ressources/mytype.ttf\"." );
    }

    //Rectangle de fond de niveau
    arriere_plan.setTexture(texture);
    arriere_plan.setScale(((float)TAILLE*level.getGrid()->getSizeX())/texture.getSize().x,
                          ((float)TAILLE*level.getGrid()->getSizeY())/texture.getSize().y);
    //Mise en place de la transparence
    arriere_plan.setColor(sf::Color(0,0,0,128));
    fond_bonbon.setColor(sf::Color(0,0,0,128));


    deplacer_bonbon_1.setScale(0.87,0.87);
    deplacer_bonbon_2.setScale(0.87,0.87);
    //Gestion du score
    score_value.setFont(font_variable);
    score_value.setScale(0.9,0.9);

    //Gestion des coups restants
    deplacement_value.setFont(font_variable);
    deplacement_value.setScale(0.9,0.9);

    //Gestion du score à atteindre
    sco_objectif_value.setFont(font_variable);
    sco_objectif_value.setScale(1,1);

    //Gestion de l'objectif du niveau
    objectif_value.setScale(0.9,0.9);
    objectif_value.setFont(font_text);
    objectif_value.setCharacterSize(16);
    objectif_value.setColor(sf::Color::Black);

}


InGame::~InGame()
{

}



// Calcule la direction du drag
int InGame::calculer_direction(int clic_x, int clic_y, int rel_x, int rel_y)
{
    // S'il n'y a pas de drag
    if(clic_x == rel_x && clic_y == rel_y)
        return DIR_NULL;

    // Calcul des variations sur x et y
    int delta_x(clic_x - rel_x), delta_y(clic_y - rel_y);
    if(delta_x < 0)
        delta_x *= -1;
    if(delta_y < 0)
        delta_y *= -1;

    // Si le drag est horizontal
    if(delta_x > delta_y)
    {
        // Si drag vers la gauche
        if(clic_x > rel_x)
        {
            return DIR_GAUCHE;
        }
        // Sinon drag vers la droite
        else
        {
            return DIR_DROITE;
        }
    }
    // Sinon si drag vertical
    else
    {
        // Si drag vers le haut
        if(clic_y > rel_y)
        {
            return DIR_HAUT;
        }
        // Sinon drag vers le bas
        else
        {
            return DIR_BAS;
        }
    }
}

// Indique si le clic est en dehors de la grille
bool InGame::clic_hors_grille(const Grid &g, unsigned int clic_x, unsigned int clic_y, unsigned int sizeX, unsigned int sizeY)
{
    // coordonnée x en dehors de la grille
    if( clic_x < ((vMode->width-g.getSizeX()*TAILLE)/2) || ((clic_x - ((vMode->width-g.getSizeX()*TAILLE)/2))/TAILLE) >= sizeX )
        return true;
    // coordonnée y en dehors de la grille
    if( clic_y < TAILLE+20+TAILLE/2 || ((clic_y - 106-TAILLE/2)/TAILLE) >= sizeY )
        return true;

    return false;
}

// Effectuer le mouvement
void InGame::effectuer_mouvement(const Grid & g, int clic_x, int clic_y, int rel_x, int rel_y)
{
    // Convertir les coordonnées du clic en coordonnées de la grille
    int depart_x( (clic_x-(vMode->width-g.getSizeX()*TAILLE)/2)/TAILLE ), depart_y( (clic_y-106-TAILLE/2)/TAILLE );

    // Si le clic est dans la grille
    if(!clic_hors_grille(g, clic_x, clic_y, g.getSizeX(), g.getSizeY()))
    {

        // Calculer la direction du drag
        int direction = calculer_direction(clic_x, clic_y, rel_x, rel_y);

        // Calculer la direction du drag
        switch (direction) {
            // Pas de drag, ne rien faire
            case DIR_NULL:
            break;

            case DIR_HAUT:
                // Si la case de départ n'est pas sur la première ligne
                if( depart_y > 0 )
                {
                    notifyObservable(true,depart_x, depart_y, depart_x, depart_y - 1);
                }
            break;

            case DIR_BAS:
                // Si la case de départ n'est pas sur la dernière ligne
                if( depart_y < g.getSizeY() - 1 )
                {
                    notifyObservable(true,depart_x, depart_y, depart_x, depart_y + 1);
                }
            break;

            case DIR_DROITE:
                // Si la case de départ n'est pas sur la dernière colonne
                if( depart_x < g.getSizeX() - 1 )
                {
                    notifyObservable(true,depart_x, depart_y, depart_x + 1, depart_y);
                }
            break;

            case DIR_GAUCHE:
                // Si la case de départ n'est pas sur la première colonne
                if( depart_x > 0)
                {
                    notifyObservable(true,depart_x, depart_y, depart_x - 1, depart_y);
                }
            break;

        } // FIN SWITCH DIRECTION

    } // FIN IF !CLIC_HORS_GRILLE
}

void InGame::masquer_case(const Level &level, int x1, int y1, int x2, int y2, bool tab[TAILLE_MAX][TAILLE_MAX]){
    arriere_bonbon.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+x1*TAILLE,20+(y1+1)*TAILLE+TAILLE/2);
    window->draw(arriere_bonbon);
    fond_bonbon.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+x1*TAILLE,20+(y1+1)*TAILLE+TAILLE/2);
    window->draw(fond_bonbon);
    int test, test2;
    if (level.getGrid()->getCell(x1,y1)->playable()) {
        test = ((Playable*)level.getGrid()->getCell(x1,y1))->getDifficulty().getName();
        switch(test){
            case 1:
                gelatine.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+x1*TAILLE,20+(y1+1)*TAILLE+TAILLE/2);
                window->draw(gelatine);
            break;
            case 2:
                gelatine2.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+x1*TAILLE,20+(y1+1)*TAILLE+TAILLE/2);
                window->draw(gelatine2);
            break;
            case 3:
                chantilly.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+x1*TAILLE,20+(y1+1)*TAILLE+TAILLE/2);
                window->draw(chantilly);
            break;
            default:break;
        }
        if (tab[x1][y1]){
            if (((Playable*)level.getGrid()->getCell(x1,y1))->getSweet() != NULL){
                test2 = ((Playable*)level.getGrid()->getCell(x1,y1))->getSweet()->getColor();
                switch(test2){
                    case 0: deplacer_bonbon_1.setTexture(bonbon_vide);
                    break;
                    case 1: deplacer_bonbon_1.setTexture(bonbon_rouge);
                    break;
                    case 2: deplacer_bonbon_1.setTexture(bonbon_bleu);
                    break;
                    case 3: deplacer_bonbon_1.setTexture(bonbon_vert);
                    break;
                    case 4: deplacer_bonbon_1.setTexture(bonbon_orange);
                    break;
                    case 5: deplacer_bonbon_1.setTexture(bonbon_violet);
                    break;
                    case 6: deplacer_bonbon_1.setTexture(bonbon_jaune);
                    break;
                }
            }
        }
        else
            deplacer_bonbon_1.setTexture(bonbon_vide);
    }

    arriere_bonbon.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+x1*TAILLE,20+(y1+1)*TAILLE+TAILLE/2);
    window->draw(arriere_bonbon);
    fond_bonbon.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+x1*TAILLE,20+(y1+1)*TAILLE+TAILLE/2);
    window->draw(fond_bonbon);
    if (level.getGrid()->getCell(x2,y2)->playable()){
        switch(test){
            case 1:
                gelatine.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+x1*TAILLE,20+(y1+1)*TAILLE+TAILLE/2);
                window->draw(gelatine);
            break;
            case 2:
                gelatine2.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+x1*TAILLE,20+(y1+1)*TAILLE+TAILLE/2);
                window->draw(gelatine2);
            break;
            case 3:
                chantilly.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+x1*TAILLE,20+(y1+1)*TAILLE+TAILLE/2);
                window->draw(chantilly);
            break;
            default:break;
        }

        if (tab[x2][y2]){
            if (((Playable*)level.getGrid()->getCell(x2,y2))->getSweet() != NULL){
                test2 = ((Playable*)level.getGrid()->getCell(x2,y2))->getSweet()->getColor();
                switch(test2){
                    case 0: deplacer_bonbon_2.setTexture(bonbon_vide);
                    break;
                    case 1: deplacer_bonbon_2.setTexture(bonbon_rouge);
                    break;
                    case 2: deplacer_bonbon_2.setTexture(bonbon_bleu);
                    break;
                    case 3: deplacer_bonbon_2.setTexture(bonbon_vert);
                    break;
                    case 4: deplacer_bonbon_2.setTexture(bonbon_orange);
                    break;
                    case 5: deplacer_bonbon_2.setTexture(bonbon_violet);
                    break;
                    case 6: deplacer_bonbon_2.setTexture(bonbon_jaune);
                    break;
                }
            }
        }
        else
            deplacer_bonbon_2.setTexture(bonbon_vide);

    }
}


// Affiche l'état temporaire de la grille
void InGame::affichage(const Level & level,bool masquer,bool drag, int x1, int y1, int x2, int y2)
{
    int test;
    std::ostringstream sco, dep, sco_obj;
    bool iscage;

    // Clear screen
    window->clear();

    // Draw the sprite
    arriere_plan.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2,20+1.5*TAILLE);

    sco << level.getScore();
    score_value.setString(sco.str());
    score_value.setPosition((vMode->width/2)-10,(TAILLE/2.2)+22+TAILLE/2);

    if(level.getHitsObjective() == -1)
    {
        dep << level.getHits();
    }
    else
    {
        dep << level.getHitsObjective() - level.getHits();
    }
    deplacement_value.setString(dep.str());
    deplacement_value.setPosition(120,(TAILLE/2.2)+22+TAILLE/2);

    sco_obj << level.getScoreObjective();
    sco_objectif_value.setString(sco_obj.str());
    sco_objectif_value.setPosition((vMode->width) - 100 - TAILLE,(TAILLE/2.2)+22+TAILLE/2);

    switch(level.getObjective()){
        case 0: objectif_value.setString("Atteindre le score pour finir le niveau");
        break;
        case 1: objectif_value.setString("Detruire la gelatine et atteindre le score pour finir le niveau");
        break;
        case 2: objectif_value.setString("Detruire la chantilly et atteindre le score pour finir le niveau");
        break;
        case 3: objectif_value.setString("Detruire les cages et atteindre le score pour finir le niveau");
        break;
    }
    int cpt = 0;
    bool tab[TAILLE_MAX][TAILLE_MAX];
    for(int i=0;i<TAILLE_MAX; i++){
        for(int j=0;j<TAILLE_MAX ; j++){
            tab[i][j] = false;
        }
    }

    do{
        window->draw(image_fond);
        window->draw(stat);
        //window->draw(arriere_plan);

        window->draw(score_value);
        window->draw(deplacement_value);
        window->draw(sco_objectif_value);
        window->draw(objectif_value);
        if(cpt < 8) cpt++;
        else{ for(int i=0;i<TAILLE_MAX; i++){
                for(int j=0;j<TAILLE_MAX ; j++){
                    tab[i][j] = false;
                }
            }
        }
        //affichage des bonbons dans la grille

        for(int i=0; i<level.getGrid()->getSizeY(); i++){
            for(int j=0;j<level.getGrid()->getSizeX(); j++){
                iscage = false;
                if (level.getGrid()->getCell(j,i)->playable()==true){
                    fond_bonbon.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+j*TAILLE,20+(i+1)*TAILLE+TAILLE/2);
                    window->draw(fond_bonbon);
                    if (((Playable*)level.getGrid()->getCell(j,i))->getDifficulty().getName()){
                        test = ((Playable*)level.getGrid()->getCell(j,i))->getDifficulty().getName();
                        switch(test){
                            case 1:
                                gelatine.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+j*TAILLE,20+(i+1)*TAILLE+TAILLE/2);
                                window->draw(gelatine);
                            break;
                            case 2:
                                gelatine2.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+j*TAILLE,20+(i+1)*TAILLE+TAILLE/2);
                                window->draw(gelatine2);
                            break;
                            case 3:
                                chantilly.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+j*TAILLE,20+(i+1)*TAILLE+TAILLE/2);
                                window->draw(chantilly);
                            break;

                            case 4:
                                iscage = true;
                            break;
                        }
                    }
                    if(((j == x1 && i == y1) || (j==x2 && i ==y2))){ tab[j][i] = true;}
                    else {
                        if (((Playable*)level.getGrid()->getCell(j,i))->getSweet() != NULL){
                            test = ((Playable*)level.getGrid()->getCell(j,i))->getSweet()->getColor();
                            switch(test){
                                case 1:
                                    rouge.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+j*TAILLE,20+(i+1)*TAILLE+TAILLE/2);
                                    window->draw(rouge);
                                break;
                                case 2:
                                    bleu.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+j*TAILLE,20+(i+1)*TAILLE+TAILLE/2);
                                    window->draw(bleu);
                                break;
                                case 3:
                                    vert.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+j*TAILLE,20+(i+1)*TAILLE+TAILLE/2);
                                    window->draw(vert);
                                break;

                                case 4:
                                    orange.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+j*TAILLE,20+(i+1)*TAILLE+TAILLE/2);
                                    window->draw(orange);
                                break;

                                case 5:
                                    violet.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+j*TAILLE,20+(i+1)*TAILLE+TAILLE/2);
                                    window->draw(violet);
                                break;

                                case 6:
                                    jaune.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+j*TAILLE,20+(i+1)*TAILLE+TAILLE/2);
                                    window->draw(jaune);
                                break;
                            }
                        }
                    }
                    if (iscage){
                        cage.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+j*TAILLE,20+(i+1)*TAILLE+TAILLE/2);
                        window->draw(cage);
                    }

                }
                else {
                    mur.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+j*TAILLE,20+(i+1)*TAILLE+TAILLE/2);
                    window->draw(mur);
                }
            }
        }

        if (masquer){
            if (cpt == 0){
                masquer_case(level,x1,y1,x2,y2,tab);
            }
            if(x1>=0 && y1>=0 && x1<level.getGrid()->getSizeX() && y1<level.getGrid()->getSizeY() && x2>=0 && y2>=0 && x2<level.getGrid()->getSizeX() && y2<level.getGrid()->getSizeY()){
                deplacer_bonbon_1.setTexture(bonbon_vide);
                deplacer_bonbon_2.setTexture(bonbon_vide);
                masquer_case(level, x1, y1, x2, y2, tab);
                window->draw(deplacer_bonbon_1);
                window->draw(deplacer_bonbon_2);
                if(drag){
                    if(x1<x2 && y1==y2){//deplacement vers la droite
                        deplacer_bonbon_1.setPosition(((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2)+x1*TAILLE +TAILLE -(x2-x1)*7*cpt,(vMode->width-level.getGrid()->getSizeY()*TAILLE)/2+y1*TAILLE);
                        deplacer_bonbon_2.setPosition(((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2)+x2*TAILLE -TAILLE +(x2-x1)*7*cpt,(vMode->width-level.getGrid()->getSizeY()*TAILLE)/2+y2*TAILLE);
                    }
                    else if(x1>x2 && y1==y2){//deplacement vers la gauche
                        deplacer_bonbon_1.setPosition(((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2)+x1*TAILLE -TAILLE +(x1-x2)*7*cpt,(vMode->width-level.getGrid()->getSizeY()*TAILLE)/2+y1*TAILLE);
                        deplacer_bonbon_2.setPosition(((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2)+x2*TAILLE +TAILLE -(x1-x2)*7*cpt,(vMode->width-level.getGrid()->getSizeY()*TAILLE)/2+y2*TAILLE);
                    }
                    else if(y1<y2&& x1 == x2){//deplacement vers le bas
                        deplacer_bonbon_1.setPosition(((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2)+x1*TAILLE,(vMode->width-level.getGrid()->getSizeY()*TAILLE)/2+y1*TAILLE +(y2-y1)*7*cpt);
                        deplacer_bonbon_2.setPosition(((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2)+x2*TAILLE,(vMode->width-level.getGrid()->getSizeY()*TAILLE)/2+y2*TAILLE -(y2-y1)*7*cpt);
                    }
                    else{//deplacement vers le haut
                        deplacer_bonbon_1.setPosition(((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2)+x1*TAILLE,(vMode->width-level.getGrid()->getSizeY()*TAILLE)/2+y1*TAILLE -(y1-y2)*7*cpt);
                        deplacer_bonbon_2.setPosition(((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2)+x2*TAILLE,(vMode->width-level.getGrid()->getSizeY()*TAILLE)/2+y2*TAILLE +(y1-y2)*7*cpt);
                    }
                }
                else{
                    deplacer_bonbon_1.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+x1*TAILLE + (x2-x1)*7*cpt*0.6,(vMode->width-level.getGrid()->getSizeY()*TAILLE)/2+y1*TAILLE- TAILLE + cpt*TAILLE/8);
                    deplacer_bonbon_2.setPosition((vMode->width-level.getGrid()->getSizeX()*TAILLE)/2+x2*TAILLE - (x2-x1)*7*cpt*0.6,(vMode->width-level.getGrid()->getSizeY()*TAILLE)/2+y1*TAILLE- TAILLE + cpt*TAILLE/8/*+(y2-y1)*7*cpt*0.6*/);
                }
            }
        }
        window->display();
        cpt++;

    }while (cpt <8);
}

void InGame::affichage_fin(bool gagne)
{
    window->draw(fin_partie);
    if(gagne)
        window->draw(victoire);
    else
        window->draw(defaite);
    window->draw(rejouer);
    window->draw(retour_menu);
    window->display();
}


/*
 * Fonctions
 *
 */
int InGame::listenAndDraw(const Level &level)
{
    unsigned int clic_x(0), clic_y(0), rel_x(0), rel_y(0);
    bool mouvement(false), clic(false), drag(false);
    int res;
    int objectif(OBJECTIVE_REACHABLE);

    affichage(level, mouvement,drag, -1,-1,-1,-1);
    // Tant que la fenêtre est ouverte
    while (window->isOpen())
    {
        if(objectif == OBJECTIVE_REACHABLE){
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

                        // Clic de la souris
                    case sf::Event::MouseButtonPressed:
                        // Si clic gauche
                        if(event.mouseButton.button == sf::Mouse::Left)
                        {
                            clic_x = event.mouseButton.x;
                            clic_y = event.mouseButton.y;
                        }
                    break;

                        // Clic relaché
                    case sf::Event::MouseButtonReleased:
                        // Si clic gauche
                        if(event.mouseButton.button == sf::Mouse::Left)
                        {
                            rel_x = event.mouseButton.x;
                            rel_y = event.mouseButton.y;
                            mouvement = true;
                        }
                    break;

                    default: break;
                } // END OF SWITCH EVENT TYPE
            } // END OF WHILE EVENT


            // Si l'utilisateur a tenté un mouvement
            if(mouvement)
            {
                // Effectuer le mouvement et ses tests
                effectuer_mouvement(*(level.getGrid()), clic_x, clic_y, rel_x, rel_y);
                // Vérifier l'objectif
                objectif = level.etat_objectif();

                // Si aucun coup n'est possible
                if(!level.getGrid()->coup_possible())
                {
                    do
                    {
                        // Redistribuer les bonbons
                        level.getGrid()->reinitializeAllSweets(level.getNbColor());
                    } while(!level.getGrid()->coup_possible());
                }
                affichage(level, mouvement, drag,clic_x,clic_y,rel_x,rel_y);
                // Remettre mouvement à faux
                mouvement = false;
            }

            // Afficher le niveau
        }
        else if(objectif == OBJECTIVE_FAILURE){
            affichage_fin(false);
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
                        // Si clic gauche
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

            // Récupérer le choix de l'utilisateur
            if(clic)
            {
                clic = false;
                res = clic_fin_niveau(clic_x, clic_y);
                if(res != CLIC_NULL)
                {
                    window->close();
                    return res;
                }
            }
        }
        // Si le joueur a gagné
        else if(objectif == OBJECTIVE_SUCCESS){
            affichage_fin(true);
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
                        // Si clic gauche
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

            // Récupérer le choix de l'utilisateur
            if(clic)
            {
                clic = false;
                res = clic_fin_niveau(clic_x, clic_y);
                if(res != CLIC_NULL)
                {
                    window->close();
                    return res;
                }
            }
        }

    } // END OF WHILE WINDOWS OPEN

    return CLIC_EXIT;
}

// Vérifie sur quel bouton à cliqué le joueur
int InGame::clic_fin_niveau(unsigned int clic_x, unsigned int clic_y)
{
    // Clic valide sur x
    if( clic_x > (vMode->width/2 - 0.5*bouton_rejouer.getSize().x/2)
        && clic_x < (vMode->width/2 - 0.5*bouton_rejouer.getSize().x/2 + 0.5*bouton_rejouer.getSize().x) )
    {
        // Clic sur rejouer
        if( clic_y > (TAILLE*5.2)
            && clic_y < ((TAILLE*5.2) + 0.5*bouton_rejouer.getSize().y) )
            return CLIC_REPLAY;

        // Clic sur menu
        else if( clic_y > (TAILLE*6)
                 && clic_y < ((TAILLE*6) + 0.5*bouton_retour_menu.getSize().y) )
            return CLIC_MENU;
    }

    return CLIC_NULL;

}

/*
 * Implémentation d'Observer
 *
 */
void InGame::notifyObservable(bool drag,int x1, int y1, int x2, int y2)
{
    observable -> update(drag, x1, y1, x2, y2);
}
void InGame::update(const Level &level,bool drag,bool , int x1, int y1, int x2, int y2)
{
    this->affichage(level,true,drag,x1,y1,x2,y2);

    sf::Time time = sf::milliseconds(25);
    sf::sleep(time);
}
void InGame::update(const Level &level)
{
    this->affichage(level,false, false,-1,-1,-1,-1);

    sf::Time time = sf::milliseconds(25);
    sf::sleep(time);
}



