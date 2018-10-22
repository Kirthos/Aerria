#include "../include/World.hpp"
#include "../include/Game.hpp"
using namespace std;

World::World()
{
    cout << "create World";
    ressourcesBox.giveWorld(this);
}
void World::init(int state, string nomMap)
{
    playerArray.push_back(new Personnage(this,&ressourcesBox));
    m_level.init(this,2048,2048,nomMap,state);
    playerArray[0]->init();
}

void World::update()
{
    playerArray[0]->update();
    m_level.update();
}

void World::render()
{
    m_level.render();
    playerArray[0]->render();

}

void World::handlePlayerInput(sf::Event &event)
{
    playerArray[0]->handlePlayerInput(event);
}

Level* World::getLevel()
{
    return &m_level;
}

Entity* World::getPerso()
{
    return playerArray[0];
}
GlobalSys* World::getGlobalSys()
{
    return &ressourcesBox;
}
