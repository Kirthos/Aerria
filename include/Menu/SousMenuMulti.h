#ifndef SOUSMENUMULTI_H_INCLUDED
#define SOUSMENUMULTI_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Multi/MainMulti.h"
#include "Multi/PacketCenter.h"

class SousMenuMulti
{
    public:
        SousMenuMulti();
        void launch(sf::Sprite cursor);
    protected:
    private:
        void render();
        void update();
        int checkBox(float x, float y);

        static sf::Sprite connexion;
        static sf::Sprite m_cursor;

        bool cacheActivated;
        static sf::Sprite retour;
        sf::Texture retourT;
        static sf::Sprite textBox;
        sf::Texture textBoxT;
        int tempCache;
        sf::Texture connexionT;

        sf::Vector2i MousePos;
        sf::Vector2f MousePosCoo;
        static sf::RectangleShape cache;

        bool m_supprActivated;

        sf::Font m_font;
        static sf::Text textIP;
        static sf::Text textPort;
        std::string m_chaineIP;
        std::string m_chainePort;

        int selected;
};

#endif // SOUSMENUMULTI_H_INCLUDED
