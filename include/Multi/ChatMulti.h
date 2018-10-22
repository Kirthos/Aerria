#ifndef CHATMULTI_H_INCLUDED
#define CHATMULTI_H_INCLUDED

#include "SingletonWindow.h"
#include <string>
#include <iostream>
#include <SFML/Network.hpp>
#include "Multi/PacketCenter.h"

class ChatMulti
{
    public:
        ChatMulti();
        void update();
        void render();
        bool getOpen();
        void open();
        void getChar(sf::Event event);
    protected:
    private:

        sf::Font m_font;
        static sf::Text chatBoxText;
        static sf::Sprite chatBox;
        sf::Texture chatBoxT;

        bool m_chatOpen;
        bool m_supprActivated;
        std::string m_wantToSend;

        int m_idMulti; // sert a reconnaitre les paquets
};

#endif // CHATMULTI_H_INCLUDED
