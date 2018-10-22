#include "../include/AABB.hpp"
#include "../include/Entity.hpp"

AABB::AABB()
{
    /*
    m_x = x;
    m_y = y;
    m_w = w;
    m_h = h;*/
}

void AABB::init(Entity* parent,sf::Vector2f taille)
{
    m_parent = parent;
    m_taille = taille;
}
void AABB::setTaille(sf::Vector2f t_taille)
{
    m_taille = t_taille;
}
sf::Vector2f AABB::getPos()
{
    return m_parent->getPosition();
}
bool AABB::testCollision(AABB block)
{
   if((block.getPos().x >= m_parent->getPosition().x + m_taille.x)      // trop à droite
	|| (block.getPos().x + block.getTaille().x <= m_parent->getPosition().x) // trop à gauche
	|| (block.getPos().y >= m_parent->getPosition().y + m_taille.y) // trop en bas
	|| (block.getPos().y + block.getTaille().y <= m_parent->getPosition().y))  // trop en haut
	{
	    return false; //pas de collision autorise le deplacement
	}
   else
          return true; //collision pas de deplacement
}
sf::Vector2f AABB::getTaille()
{
    return m_taille;
}
