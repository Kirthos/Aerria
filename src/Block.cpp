#include "../include/Block.hpp"

using namespace std;

Block::Block()
{
}
void Block::setBlock(int tiles)
{
    m_tiles = tiles;
    switch (m_tiles) {
        case 0:
            m_armor = 0;
            m_life = 0;
            m_name = "Air";
            m_mine = false;
            m_collision = false;
            break;
        case 1:
            m_armor = 0;
            m_life = 5;
            m_name = "Dirt";
            m_mine = true;
            m_collision = true;
            break;
        case 2:
            m_armor = 0;
            m_life = 6;
            m_name = "Stone";
            m_mine = true;
            m_collision = true;
            break;
        case 3:
            m_armor = 0;
            m_life = 7;
            m_name = "Coal";
            m_mine = true;
            m_collision = true;
            break;
        case 4:
            m_armor = 1;
            m_life = 12;
            m_name = "Silver";
            m_mine = true;
            m_collision = true;
            break;
        case 5:
            m_armor = 1;
            m_life = 12;
            m_name = "Fossile";
            m_mine = true;
            m_collision = true;
            break;
        case 6:
            m_armor = 0;
            m_life = 8;
            m_name = "Iron";
            m_mine = true;
            m_collision = true;
            break;
        case 7:
            m_armor = 1;
            m_life = 15;
            m_name = "Gold";
            m_mine = true;
            m_collision = true;
            break;
        case 8:
            m_armor = 2;
            m_life = 20;
            m_name = "Diamond";
            m_mine = true;
            m_collision = true;
            break;
        default:
            m_armor = 0;
            m_life = 0;
            m_name = "Air";
            m_mine = false;
            m_tiles = 0;
            m_collision = false;
  }
}
bool Block::damage(int puissance)
{
    int degats = puissance - m_armor;
    if(degats <0)
        degats = 0;
    m_life -= degats;
    if(m_life<=0)
        return true;
    else
        return false;
}
bool Block::getCollision()
{
    return m_collision;
}
int Block::getTiles()
{
    return m_tiles;
}
bool Block::getMine()
{
    return m_mine;
}
string Block::getName()
{
    return m_name;
}
void Block::decris()
{
    cout<<"--------------------------------"<<endl<<"Tiles : "<<m_tiles<<endl<<"Armor : "<<m_armor<<endl<<"Life : "<<m_life<<endl<<"Name : "<<m_name<<endl<<"Minable ? : "<<m_mine<<endl;
}
