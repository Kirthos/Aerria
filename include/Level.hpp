#ifndef LEVEL_HPP_INCLUDED
#define LEVEL_HPP_INCLUDED

#include "PerlinNoise.hpp"
#include "Region.hpp"
#include "entTypeEnum.h"

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>

#include <vector>
#include <map>
#include <stack>

#include <windows.h>

class World;

class Level
{
  public:
    int getRegioSize();

    Level();
    void init(World *t_world, int const largeur, int const hauteur, std::string nomMap,int const state);
    void loadLevel();
    void save();
    void create();
    std::vector<std::vector<int> > getLevel();
    int getSize();
    int getHauteur();
    int getLargeur();
    int getDivision();
    void setLevel(int x,int y);
    void update();
    void render();

    void receiveLoadSignal(sf::Vector2i t_value);
    void receiveUnloadSignal(sf::Vector2i t_value);

    int addEntity(entType type); //la valeur de renvoi est en fait l'id de l'entity qui a été crer en vue de son initialisation, et de sa gestion
    void removeEntity(int id);

    Entity* getEntityById(int id);

    void setBlock(sf::Vector2i pos, int type);  // en cordonnee absolue, la fonction divise par 32 d'elle même, ca permet plus de flexibilité avec les entité
    int getBlock(sf::Vector2i pos);

    World* getWorld();
    sf::Vector2i getVecRegion();
    Region* getRegion(sf::Vector2i pos);
protected:
    void updateRegion();
    bool checkForUnload(sf::Vector2i t_value);

private:

    EntityStdStorage m_entityStdStorage;

    std::string m_nomMap;
    int m_taille;
    int m_hauteur;
    int m_largeur;
    int m_divisionRegion;
    std::vector<std::vector<int> > m_level;
    std::vector<std::vector<Region*> > m_regions;
    int m_nombreRegions;
    World *m_world;

    int currentId;
    std::vector<Entity*> m_entityArray; //Le vector qui contient toute les entity
    std::map<int, int> m_entityArrayIndex;
    std::stack<int> m_entityArrayFreeSpace;

    std::vector<sf::Vector2i> regionLoadOrder;
    std::vector<sf::Vector2i> regionUnloadOrder;


    Region* regTampon;
    std::stack<Region*> regionContainer[2];
};


#endif // LEVEL_HPP_INCLUDED
