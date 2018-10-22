#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "GlobalSys.hpp"
#include "AABB.hpp"
#include "Block.hpp"
#include "Region.hpp"
#include "Inventory.hpp"
#include "Item.hpp"

class World;

class Entity
{
public:
    Entity(World* t_world, GlobalSys* t_ressourceBox);
    virtual void update();
    virtual void render();
    virtual void handlePlayerInput(sf::Event &event);
    void setWorld(World* t_world);
    World* getWorld();
    void setName(std::string t_name);
    std::string getName();
    void setMoveOrientation(float t_orientation);
    float getMoveOrientation();
    void setSpeed(float t_speed);
    float getSpeed();
    void setPosition(float t_x, float t_y);
    void setPosition(sf::Vector2f t_pos);
    sf::Vector2f getPosition();
    bool getAlive();
    void destroy();
    virtual void init();
    void processGravity();
    virtual void Move();
    virtual int getId();
    virtual void setId(int temp_id);
    virtual Inventory getInventory();
    virtual void save(std::string nomMap);
    virtual void load(std::string nomMap);
    virtual void setItem(Item t_matchingItem);
    GlobalSys* getGSys();
    virtual bool getClicked(){}
protected:
    int id;



    bool checkCollision();
    bool checkCollisionSol();
    GlobalSys* m_ressourceBox;

    sf::Sprite m_sprite;
    World* m_world;

    std::string m_name;
    bool m_alive;
    sf::Vector2f m_pos;
    float m_speed;
    float m_orientation;
    bool m_isGhost;
    bool m_isFly;
    bool m_toucheSol;
    int m_gravity;
    sf::Vector2f m_deplacement;
    float m_maxSpeed;

    AABB m_hitbox;
    sf::Clock gravity;

};

class entityError : public Entity
{
public:
    entityError(World* t_world, GlobalSys* t_ressourceBox);
    void update(){ std::cout << "fuck";};
};

#endif // ENTITY_H_INCLUDED
