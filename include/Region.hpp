#ifndef REGION_H
#define REGION_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Tilemap.hpp"
#include "SingletonWindow.h"
class Level;
class GlobalSys;

class Entity;

class Region
{
    public:
        Region(Level* t_level);
        bool getIsLoaded();
        void setIsLoaded(bool isLoaded);
        void setPos(sf::Vector2i pos);
        sf::Vector2i getPos();
        void decris();
        std::vector<std::vector<int> > getBlocks();
        int getBlock(sf::Vector2i posBlock);
        void setBlocks(std::vector<std::vector<int> > blocks);
        void setBlock(sf::Vector2i posBlock,int id);
        void render();
        void loadTileMap();
        void unload();
        void creerEntity(Entity* test);
        void update();
    protected:
    private:
        Level* m_level;
        GlobalSys* m_globalBox;
        sf::Vector2i m_pos;
        bool m_isLoaded;
        std::vector<std::vector<int> > m_block;
        TileMap m_map;
        std::vector<Entity*> entityArray;
        int temptemp;
};

#endif // REGION_H
