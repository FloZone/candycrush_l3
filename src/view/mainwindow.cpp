#include "view/mainwindow.h"



MainWindow::MainWindow(std::string name, int width, int height)
{
    observable = NULL;

    if(width == -1 || height == -1)
        throw MessageError("mainwindow.cpp"
                           , "MainWindow::MainWindow(int, int)"
                           , "Invalid window dimentions specified");
    else
    {
        vMode = new sf::VideoMode(width, height);
        window = new sf::RenderWindow(*vMode, name,sf::Style::Close);
        window -> setFramerateLimit(60);
    }
}

MainWindow::~MainWindow()
{
    if(window)
        delete window;

    if(vMode)
        delete vMode;
}

/*
 * Fonctions
 *
 */
int MainWindow::listenAndDraw(const Level &)
{
    return 0;
}


/*
 * Implémentation d'Observer
 *
 */
void MainWindow::notifyObservable(int, int, int, int)
{

}
void MainWindow::update(const Level &)
{

}
