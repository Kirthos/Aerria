#include "../include/Region.hpp"
#include "../include/Entity.hpp"
#include "../include/Level.hpp"
#include "../include/World.hpp"

using namespace std;

Region::Region(Level* t_level)
{
    m_level = t_level;
    m_globalBox = t_level->getWorld()->getGlobalSys();
    m_isLoaded = false;
    m_pos.x = 0;
    m_pos.y = 0;
    m_block.resize(255);
    for(int i=0;i<m_block.size();i++)
        m_block[i].resize(255);
    temptemp = 0;
}
sf::Vector2i Region::getPos()
{
    return m_pos;
}
bool Region::getIsLoaded()
{
    return m_isLoaded;
}
void Region::setPos(sf::Vector2i pos)
{
    m_pos = pos;
}
void Region::setIsLoaded(bool isLoaded)
{
    m_isLoaded = isLoaded;
}
void Region::decris()
{
    cout<<"------------------------------------"<<endl<<"region : "<<m_pos.x<<"-"<<m_pos.y<<endl<<"Loaded ? : "<<m_isLoaded<<endl;
}
vector<vector<int> > Region::getBlocks()
{
    return m_block;
}
void Region::setBlocks(vector<vector<int> > blocks)
{
    m_block = blocks;
}
void Region::setBlock(sf::Vector2i posBlock, int id)
{
    m_block[posBlock.x][posBlock.y] = id;
    m_map.reloadBlock(posBlock,id);
}
int Region::getBlock(sf::Vector2i posBlock)
{
    return m_block[posBlock.x][posBlock.y];
}
void Region::loadTileMap()
{
    if(!m_isLoaded)
    {
        if(m_map.load("tileset.png", sf::Vector2u(32,32), m_block, m_block.size(), m_block.size()))
        {
            //Region bien load
            m_map.setPosition(m_block.size()*32*m_pos.x,m_block.size()*32*m_pos.y);
            m_level->receiveLoadSignal(m_pos);
            m_isLoaded = true;

        }
        else
        {
            cout<<"Impossible de charger la region : "<<m_pos.x<<"/"<<m_pos.y<<" !"<<endl;
            m_isLoaded = false;
        }
    }
}
void Region::unload()
{
    m_level->receiveUnloadSignal(m_pos);
    m_isLoaded = false;
}
void Region::render()
{
    sf::RenderWindow& window = Window::getWindow();
    window.draw(m_map);
    for(unsigned int i = 0;i<entityArray.size();i++) entityArray[i]->render();
}
void Region::update()
{
    temptemp++;
    if(temptemp==3)
    {
    for(unsigned int i = 0;i<entityArray.size();i++) entityArray[i]->update();
    temptemp = 0;
    }
}
void Region::creerEntity(Entity* test)
{
    cout<<entityArray.size()<<endl;
    entityArray.push_back(test);
}
