#ifndef SINGLETONWINDOW_H_INCLUDED
#define SINGLETONWINDOW_H_INCLUDED
#include <SFML/Graphics.hpp>

class Window
{
public:
    static sf::RenderWindow& getWindow();
    static void closeWindow();
private:
    static bool alreadyCreated;
};
#endif // SINGLETONWINDOW_H_INCLUDED
