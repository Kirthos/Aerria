#include "../../include/Menu/Menu.hpp"
using namespace std;
sf::Sprite SousMenuMulti::connexion;
sf::Sprite SousMenuMulti::m_cursor;
sf::Sprite SousMenuMulti::retour;
sf::Sprite SousMenuMulti::textBox;

sf::Text SousMenuMulti::textIP;
sf::Text SousMenuMulti::textPort;

sf::RectangleShape SousMenuMulti::cache;

SousMenuMulti::SousMenuMulti()
{
    connexionT.loadFromFile("ressources/connexion.png");
    connexion.setTexture(connexionT);
    connexion.setPosition(214.5, 307.5);
    connexion.setScale(0.8, 0.8);

    retourT.loadFromFile("ressources/retour.png");
    retour.setTexture(retourT);
    retour.setPosition(214.5, 381.5);
    retour.setScale(0.8, 0.8);

    sf::Vector2f cacheSize(216, 64);
    cache.setFillColor(sf::Color(0, 0, 0, 50));
    cache.setSize(cacheSize);

    textBoxT.loadFromFile("ressources/textBox.png");
    textBox.setTexture(textBoxT);
    textBox.setPosition(214.5, 233.5);
    textBox.setScale(0.8, 0.8);

    m_font.loadFromFile("arial.ttf");

    textIP.setFont(m_font);
    textIP.setCharacterSize(18);
    textIP.setColor(sf::Color::Black);
    textIP.setPosition(283,230);

    textPort.setFont(m_font);
    textPort.setCharacterSize(18);
    textPort.setColor(sf::Color::Black);
    textPort.setPosition(283,257);

    m_supprActivated = false;
}
void SousMenuMulti::launch(sf::Sprite cursor)
{
    m_cursor = cursor;
    sf::Event event;
    sf::RenderWindow& mWindow = Window::getWindow();
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::seconds(1.f/20.f);
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
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Delete || event.key.code == sf::Keyboard::BackSpace)
                {
                    m_supprActivated = true;
                }
            }
            else if (event.type == sf::Event::TextEntered && event.key.code != sf::Keyboard::BackSpace)
            {
                if (event.text.unicode < 128 && selected == 1)
                {
                    m_chaineIP += static_cast<char>(event.text.unicode); // on recupere les caracteres entré par l'utilisateur
                    textIP.setString(m_chaineIP);
                }
                else if(event.text.unicode < 128 && selected == 2)
                {
                    m_chainePort += static_cast<char>(event.text.unicode); // on recupere les caracteres entré par l'utilisateur
                    textPort.setString(m_chainePort);
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Delete || event.key.code == sf::Keyboard::BackSpace)
                {
                    m_supprActivated = false;
                }
            }
        }
        render();
    }
}
void SousMenuMulti::render()
{
    sf::RenderWindow& mWindow = Window::getWindow();

    mWindow.clear(sf::Color::White);

    mWindow.draw(connexion);
    mWindow.draw(retour);
    mWindow.draw(textBox);

    if (cacheActivated)
        mWindow.draw(cache);
    mWindow.draw(textIP);
    mWindow.draw(textPort);

    mWindow.draw(m_cursor);

    mWindow.display();
}
void SousMenuMulti::update()
{
    if(m_supprActivated && m_chaineIP.size() > 0 && selected == 1)
    {
        m_chaineIP.erase(m_chaineIP.size() - 1);
        textIP.setString(m_chaineIP);
    }
    else if(m_supprActivated && m_chainePort.size() > 0 && selected == 2)
    {
        m_chainePort.erase(m_chainePort.size() - 1);
        textPort.setString(m_chainePort);
    }

    sf::RenderWindow& mWindow = Window::getWindow();

    MousePos = sf::Mouse::getPosition(mWindow);
    MousePosCoo = mWindow.mapPixelToCoords(MousePos);
    m_cursor.setPosition(MousePosCoo);
    tempCache = checkBox(MousePosCoo.x, MousePosCoo.y);
    if (tempCache == 1)
    {
        cache.setPosition(214.5, 307.5);
        cacheActivated = true;
    }

    else if (tempCache == 2)
    {
        cache.setPosition(214.5, 381.5);
        cacheActivated = true;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
    {
        tempCache = checkBox(MousePosCoo.x, MousePosCoo.y);
        if (tempCache != 0)
        {
            if(tempCache == 1)
            {
                PacketCenter::connexion(m_chaineIP, m_chainePort);
            }
            if (tempCache == 2)
            {
                Menu menu;
                menu.run();
            }
            if (tempCache == 3)
                selected = 1;
            if (tempCache == 4)
                selected = 2;
        }
    }

}
int SousMenuMulti::checkBox(float x, float y)
{
    if ((x > 214.5 && x < 430.5) && (y > 307.5 && y < 371.5))
    {
        return (1);// bouton connexion
    }
    else if ((x > 214.5 && x < 430.5) && (y > 381.5 && y < 445.5))
    {

        return (2);// bouton retour
    }
    else if ((x > 283.5 && x < 410.5) && (y > 235.5 && y < 246.5))
    {
        return (3);// textbox1
    }
    else if ((x > 283.5 && x < 410.5) && (y > 262.5 && y < 275.5))
    {
        return (4);// textbox2
    }
    cacheActivated = false;
    return (0);
}
