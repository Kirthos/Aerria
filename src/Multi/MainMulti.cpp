#include "../../include/Multi/MainMulti.h"
using namespace std;

void MainMulti::run()
{
    sf::RenderWindow& mWindow = Window::getWindow();
    mWindow.setMouseCursorVisible(true);
    sf::Event event;
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::seconds(1.f/20.f);

    m_verifChat = true;

    while (mWindow.isOpen())
    {
        update();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            update();
        }
        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Window::closeWindow();
            }
            if (chat.getOpen())// si le chat est ouvert il gere aussi les événements pour récuperer ce que le joueur veut écrire
            {
                chat.getChar(event);
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Return && m_verifChat == true)
                {
                    chat.open();
                    m_verifChat = false; // pour éviter que le chat se referme instantanément quand on appuie
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Return)
                {
                    m_verifChat = true; // pour éviter que le chat se referme instantanément quand on appuie
                }
            }
        }
        render();
    }
}
void MainMulti::update()
{
    chat.update();
}
void MainMulti::render()
{
    sf::RenderWindow& mWindow = Window::getWindow();
    mWindow.clear(sf::Color::Red);
    chat.render();
    mWindow.display();
}
