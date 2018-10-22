#ifndef MAINMULTI_H_INCLUDED
#define MAINMULTI_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "SingletonWindow.h"
#include <iostream>
#include <SFML/Network.hpp>
#include "ChatMulti.h"

class MainMulti
{
    public:
        void run();
    protected:
    private:
        void render();
        void update();
        ChatMulti chat;
        bool m_verifChat;
};
#endif // MAINMULTI_H_INCLUDED
