#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.hpp"
#include "Outils.hpp"
#include "Item.hpp"
#include "DropedItem.hpp"
#include "Inventory.hpp"
#include "allEnum.h"

class Level;

class World;

class Personnage : public Entity
{
    public:
        Personnage(World* t_world, GlobalSys* t_ressourceBox);

        void init();
        void render();
        void update();
        void acceleration();
        void handlePlayerInput(sf::Event &event);

        Inventory getInventory();
        sf::Vector2i regionPerso();
        void save(std::string m_nomMap);
        void load(std::string m_nomMap);
        void setCanMine(bool t_canMine);
        bool getClicked();
    protected:
    private:
        void loadRegion();
        void unloadRegion();
        void loadMap();
        void clicked(int click);
        void decoupAnim(int state);
        void Move();

        sf::View viewWindow;
        Level *m_level;
        sf::Vector2i m_numRegionPerso;
        Outils pioche;
        sf::Clock mining;
        Block miningBlock;
        bool m_depLeft;
        bool m_depRight;
        bool m_jump;
        bool m_inventory;
        bool m_invIsOpen;
        bool m_reset;
        bool m_trieInv;
        bool m_click;
        sf::Vector2i posView;
        sf::Texture* m_texture[10];
        float m_animCount;
        int tempAnim;
        int m_puissJump;
        int m_porteeMiningBlock;
        bool m_canMine;

        Inventory inventaire;

        sf::Text m_version;
        int m_control[7];
};

#endif // PERSONNAGE_H
