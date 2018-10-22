#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include <SFML/Audio.hpp>
#include "Game.hpp"
#include "SingletonWindow.h"
#include "Menu/SousMenuMulti.h"
#include <iostream>

using namespace std;

class Menu
{
public:
    Menu();
    void run();
protected:
    void update();
    const void render();
    int checkBox(float x, float y);
    void updateCloud();
    void updateSM();
    bool cacheActivated;
    sf::RectangleShape cache;

//son
    sf::Music fond;

//textures

    sf::Texture cursorT;
    sf::Texture backPlanT;
    sf::Sprite backPlan;

    sf::Texture bouton1T; //commande normal
    sf::Texture bouton2T; //option
    sf::Texture bouton3T; //quit
    sf::Texture boutonMultiT;

    sf::Sprite cursor;

    sf::Sprite bouton1;
    sf::Sprite bouton3;
    sf::Sprite bouton2;
    sf::Sprite boutonMulti;

//cloud
    sf::Texture cloudT;

    sf::Sprite cloud;
    sf::Vector2f cloudPos;
    sf::Sprite cloud2;
    sf::Vector2f cloud2Pos;

//moon / sun
    sf::Vector2f sunPos;
    sf::Vector2f moonPos;

    sf::Texture sunT;
    sf::Texture moonT;

    sf::Sprite sun;
    sf::Sprite moon;

//    sf::Mouse mouse;
    sf::Vector2i MousePos;
    sf::Vector2f MousePosCoo;

    sf::View mainView;

//temp
int tempCache;

//Sous Menu
SousMenuMulti m_sousMenuMulti;
};

#endif // MENU_HPP_INCLUDED
