#ifndef DROPEDITEM_H
#define DROPEDITEM_H

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <iostream>
#include "Item.hpp"
#include "SingletonWindow.h"

class World;

class DropedItem : public Entity
{
public:
    DropedItem(World* t_world, GlobalSys* t_ressourceBox, Item t_matchingItem);
    DropedItem(World* t_world, GlobalSys* t_ressourceBox);
    Item pickUp();
    void attract();
    void update();
    void render();
    void setItem(Item t_matchingItem);
    void Move();
protected:
    Item m_matchingItem;

    //propriété
    float m_attractSpeed;


    int distanceAttract;

    //var temp attract
    float distanceItemCible;
    float distanceRepereCible;
    float distanceItemRepere;
    float temp1;
    float temp2;
    float temp3;

    sf::Clock m_lifeTime;
    World *m_world;
    bool m_veille;
    bool m_isAttract;
    bool m_temp;
};

#endif // DROPEDITEM_H
