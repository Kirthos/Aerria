#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <iostream>

class Block
{
    public:
        Block();
        void setBlock(int tiles);
        bool damage(int puissance);
        int getTiles();
        void decris();
        bool getMine();
        bool getCollision();
        std::string getName();
    protected:
        int m_life;
        int m_armor;
        int m_tiles;
        std::string m_name;
        bool m_mine;
        bool m_collision;
    private:
};

#endif // BLOCK_H
