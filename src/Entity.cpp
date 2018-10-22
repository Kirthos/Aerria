#include "../include/Entity.hpp"
#include "../include/World.hpp"
#include "../include/Game.hpp"

Entity::Entity(World* t_world, GlobalSys* t_ressourceBox)
{
    m_ressourceBox = t_ressourceBox;
    m_world = t_world;
    m_alive = true;
    m_isFly = false;
    m_isGhost = false;
    m_toucheSol = false;
    m_gravity = 1;
    m_speed = 8;
    m_maxSpeed = 8;
}
entityError::entityError(World* t_world, GlobalSys* t_ressourceBox) : Entity(t_world,t_ressourceBox)
{

}
int Entity::getId()
{
    return id;
}
void Entity::setId(int temp_id)
{
    id = temp_id;
}
void Entity::update()
{
    std::cout << "up^dateInEntity\n";
}
void Entity::render()
{

}
bool Entity::checkCollision()
{
    Block block;

    sf::Vector2i posBlock1 = sf::Vector2i(int((m_pos.x+15)/32),int(m_pos.y/32)); // recupere le block en haut a gauche du perso
    sf::Vector2i posBlock2 = sf::Vector2i(int((m_pos.x+15)/32+m_hitbox.getTaille().x/32),int(m_pos.y/32+m_hitbox.getTaille().y/32)); // recupere le block en bas a droite du perso
    sf::Vector2i nbrBlockTest = sf::Vector2i(posBlock1.x - posBlock2.x-1, posBlock1.y - posBlock2.y-1); //recupere le nombre de block a tester en x et y
    if(nbrBlockTest.x <0)nbrBlockTest.x *=-1; //equivalent a une valeur absolue
    if(nbrBlockTest.y <0)nbrBlockTest.y *=-1;
    for(int i=0; i<nbrBlockTest.x; i++)
    {
        for(int j = 0; j<nbrBlockTest.y; j++)
        {
            sf::Vector2i regionBlockATest = sf::Vector2i((posBlock1.x+i)/256,(posBlock1.y+j)/256); //recupere la position de la region
            sf::Vector2i blockATest = sf::Vector2i((posBlock1.x+i)%256,(posBlock1.y+j)%256); //recupere la position du block a test dans la region

            Region* test = m_world->getLevel()->getRegion(regionBlockATest); //recupere un pointeur sur la region
            block.setBlock(test->getBlock(blockATest)); //creer le block en fonction de la texture a la postion
            if(block.getCollision()) //verifie si on peut passer a travers le block
            {
                return false; // interdit de passer
            }
        }
    }
    return true; //droit de passer
}
bool Entity::checkCollisionSol()
{
    Block block;
    int posBlock1 = int(m_pos.x+15)/32;
    int posBlock2 = int((m_pos.x+15)/32+m_hitbox.getTaille().x/32);
    int posBlockY = int((m_pos.y+15)/32+m_hitbox.getTaille().y/32);
    int nbrBlockTest = posBlock1 - posBlock2-1;
    if(nbrBlockTest <0)nbrBlockTest *=-1;
    for(int i=0; i<nbrBlockTest; i++)
    {
        sf::Vector2i regionBlockATest = sf::Vector2i((posBlock1+i)/256,(posBlockY)/256);
        sf::Vector2i blockATest = sf::Vector2i((posBlock1+i)%256,(posBlockY)%256);

        Region* test = m_world->getLevel()->getRegion(regionBlockATest);
        block.setBlock(test->getBlock(blockATest));
        if(block.getCollision())
        {
            return false; // interdit de passer
        }
    }
    return true; //droit de passer
}
void Entity::processGravity()
{
    if(!m_isFly)
    {
        if(m_deplacement.y < m_maxSpeed)
            m_deplacement.y += m_speed;
    }
}
void Entity::Move()
{
    m_pos.x += m_deplacement.x;
    if(!checkCollision() || m_pos.x > m_world->getLevel()->getLargeur()*32-200 || m_pos.x < 116)
    {
        m_pos.x -= m_deplacement.x;
        m_deplacement.x = 0;
    }
    if(m_toucheSol)
    {
        if(gravity.getElapsedTime().asSeconds()>1)
        {
            gravity.restart();
            m_pos.y += m_deplacement.y;
            if(!checkCollisionSol() || m_pos.y > m_world->getLevel()->getHauteur()*32-200 || m_pos.y < 116)
            {
                m_pos.y -= m_deplacement.y;
                m_deplacement.y = 0;
                m_toucheSol = true;
            }
            else
            {
                m_toucheSol = false;
            }
        }
    }
    else
    {
        m_pos.y += m_deplacement.y;
        if(!checkCollisionSol() || m_pos.y > m_world->getLevel()->getHauteur()*32-200 || m_pos.y < 116)
        {
            m_pos.y -= m_deplacement.y;
            m_deplacement.y = 0;
            m_toucheSol = true;
        }
        else
        {
            m_toucheSol = false;
        }
    }
}
void Entity::setWorld(World* t_world)
{
    m_world = t_world;
}
World* Entity::getWorld()
{
    return(m_world);
}
void Entity::setName(std::string t_name)
{
    m_name = t_name;
}
std::string Entity::getName()
{
    return(m_name);
}
void Entity::setMoveOrientation(float t_orientation)
{
    m_orientation = t_orientation;
}
void Entity::setSpeed(float t_speed)
{
    m_speed = t_speed;
}
float Entity::getSpeed()
{
    return (m_speed);
}
void Entity::setPosition(float t_x, float t_y)
{
    m_pos.x = t_x;
    m_pos.y = t_y;
}
void Entity::setPosition(sf::Vector2f t_pos)
{
    m_pos = t_pos;
}
sf::Vector2f Entity::getPosition()
{
    return (m_pos);
}
bool Entity::getAlive()
{
    return (m_alive);
}
void Entity::destroy()
{
    m_alive = false;
}
void Entity::init()
{

}
void Entity::handlePlayerInput(sf::Event &event)
{

}
Inventory Entity::getInventory()
{

}
void Entity::save(std::string nomMap)
{

}
void Entity::load(std::string nomMap)
{

}
GlobalSys* Entity::getGSys()
{
    return m_ressourceBox;
}

void Entity::setItem(Item t_matchingItem)
{

}
