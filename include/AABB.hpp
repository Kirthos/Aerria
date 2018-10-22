#ifndef AABB_H
#define AABB_H

#include <SFML/Graphics.hpp>

class Entity;

class AABB
{
    public:
        AABB();
        void init(Entity* parent,sf::Vector2f taille);
        void setTaille(sf::Vector2f t_taille);
        bool testCollision(AABB test);
        sf::Vector2f getTaille();
        sf::Vector2f getPos();
        void setPos(sf::Vector2f pos);
    protected:
    private:
        sf::Vector2f m_taille;
        Entity* m_parent;
};

#endif // AABB_H
