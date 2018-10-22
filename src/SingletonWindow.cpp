#include "../include/SingletonWindow.h"

sf::RenderWindow fenetre;
bool Window::alreadyCreated = false;

sf::RenderWindow& Window::getWindow()
{
    if(!alreadyCreated)
    {
        fenetre.create(sf::VideoMode(800, 800), "Aerria V0.2-INDEV");
        alreadyCreated = true;
    }
    return fenetre;
}
void Window::closeWindow()
{
    fenetre.close();
}
