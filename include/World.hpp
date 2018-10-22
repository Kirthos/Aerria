#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Personnage.hpp"
#include "GlobalSys.hpp"
#include <vector>
#include "Level.hpp"
#include "SingletonWindow.h"
#include <iostream>

class Game;

class World
{
    public:
        World();
        void init(int state, std::string nomMap);
        void update();
        void render();
        void handlePlayerInput(sf::Event &event);
        Level* getLevel();
        Entity* getPerso();
        GlobalSys* getGlobalSys();
    protected:
        Game *m_game;
        GlobalSys ressourcesBox;
        Level m_level;
        std::vector<Entity*> playerArray;
};

#endif // WORLD_H
