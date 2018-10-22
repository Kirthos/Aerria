#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "SingletonWindow.h"

class Game
{
public :
    sf::View mainView;
    Game(int state, std::string nomMap);
    void run();
private :
    void handlePlayerInput(sf::Event &event);
    void update();
    void render();
private :

    World m_world;
};

#endif // GAME_HPP_INCLUDED
