#include "../include/DropedItem.hpp"
#include "../include/World.hpp"

DropedItem::DropedItem(World* t_world, GlobalSys* t_ressourceBox, Item t_matchingItem) : Entity(t_world,t_ressourceBox)
{
    m_matchingItem = t_matchingItem;
    distanceItemRepere = 10;
    m_attractSpeed = 5;
    m_sprite.setTexture(*t_ressourceBox->requestTexture("tileset.png",sf::IntRect(32*m_matchingItem.getID(),0,32,32)));
    m_sprite.setScale(0.5,0.5);
    m_hitbox.setTaille(sf::Vector2f(0,0));
    m_world = t_world;
    distanceAttract = 200;
    m_speed = 15;
    m_veille = false;
    m_isAttract = false;
    m_temp = false;
}

DropedItem::DropedItem(World* t_world, GlobalSys* t_ressourceBox) : Entity(t_world,t_ressourceBox)
{
    distanceItemRepere = 10;
    m_attractSpeed = 5;
    m_sprite.setScale(0.5,0.5);
    m_hitbox.setTaille(sf::Vector2f(0,0));
    m_world = t_world;
    distanceAttract = 200;
    m_speed = 15;
}


void DropedItem::update()
{
    if(m_alive)
    {
        if(m_toucheSol)
            m_veille = true;
        if(m_world->getPerso()->getClicked())
            m_veille = false;
        if(!m_veille)
            processGravity();
        attract();
        if(!m_veille)
        {
            Move();
            m_sprite.setPosition(m_pos.x,m_pos.y);
            if(m_lifeTime.getElapsedTime().asSeconds()>180)
            {
                m_alive = false;
            }
        }
    }
}

void DropedItem::render()
{
    sf::RenderWindow& mWindow = Window::getWindow();
    if(m_alive)
        mWindow.draw(m_sprite);
}

Item DropedItem::pickUp()
{
    return m_matchingItem;
}
void DropedItem::Move()
{
    m_pos.x += m_deplacement.x;
    if(m_toucheSol)
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
    else
    {
        m_pos.y += m_deplacement.y;
        if(!m_isAttract)
        {
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
}
void DropedItem::attract()
{
    sf::Vector2f t_attractTarget = m_world->getPerso()->getPosition();
    t_attractTarget.x +=32;
    t_attractTarget.y +=48;
    if(abs(t_attractTarget.x - m_pos.x)<distanceAttract && abs(t_attractTarget.y - m_pos.y)<distanceAttract)
    {
        m_veille = false;
        m_isAttract = true;
        if(t_attractTarget.x < m_pos.x)
            m_deplacement.x = -m_speed;
        else
            m_deplacement.x = m_speed;
        if(t_attractTarget.y < m_pos.y)
            m_deplacement.y = -m_speed;
        else
            m_deplacement.y = m_speed;
        if(abs(t_attractTarget.x - m_pos.x)<m_speed && abs(t_attractTarget.y - m_pos.y)<m_speed)
        {
            m_world->getPerso()->getInventory().addItem(pickUp());
            m_alive = false;
        }
    }
    else
    {
        m_deplacement.x = 0;
        m_isAttract = false;
    }
}
void DropedItem::setItem(Item t_matchingItem)
{
    m_matchingItem = t_matchingItem;
}
