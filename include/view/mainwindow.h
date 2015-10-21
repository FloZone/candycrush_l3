#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../controller/observer.h"
#include "../models/grid.h"
#include "../models/level.h"
#include "../exceptions/error_value.h"


class MainWindow : public Observer
{
public:
    MainWindow(std::string name = "Unknown", int width = -1, int height = -1);
    virtual ~MainWindow();

    virtual int listenAndDraw(const Level &);

    /* Implémentation d'Observer */
    virtual void notifyObservable(int,int,int,int);
    virtual void update(const Level &);

protected:

    sf::RenderWindow *window;
    sf::VideoMode *vMode;

};

#endif // MAINWINDOW_H
