#include "../../include/Multi/ChatMulti.h"
using namespace std;
sf::Sprite ChatMulti::chatBox;
sf::Text ChatMulti::chatBoxText;

ChatMulti::ChatMulti()
{
    chatBoxT.loadFromFile("ressources/chatMulti.png");
    chatBox.setTexture(chatBoxT);
    chatBox.setPosition(0, 600);
    chatBox.setScale(0.8, 0.8);

    m_font.loadFromFile("arial.ttf");

    chatBoxText.setFont(m_font);
    chatBoxText.setCharacterSize(18);
    chatBoxText.setColor(sf::Color::Black);
    chatBoxText.setPosition(0,600);

    m_chatOpen = false;
    m_supprActivated = false;

    m_idMulti = 1;
}
void ChatMulti::update()
{
    if(m_supprActivated && m_wantToSend.size() > 0)
    {
        m_wantToSend.erase(m_wantToSend.size() - 1);
        chatBoxText.setString(m_wantToSend);
    }
}
void ChatMulti::render()
{
    sf::RenderWindow& mWindow = Window::getWindow();
    if(m_chatOpen)
    {
        mWindow.draw(chatBox);
        mWindow.draw(chatBoxText);
    }

}
void ChatMulti::open()
{
    if(m_chatOpen)
    {
        m_chatOpen = false;
        if(m_wantToSend.size() > 1) // pour éviter d'overflow en envoyant des chaines vides
        {
            sf::Packet packet;
            packet << m_idMulti << m_wantToSend;
            PacketCenter::sendToTcp(packet);
            m_wantToSend.clear();
        }
    }
    else
        m_chatOpen = true;
}
bool ChatMulti::getOpen()
{
    return m_chatOpen;
}
void ChatMulti::getChar(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Delete || event.key.code == sf::Keyboard::BackSpace)
        {
            m_supprActivated = true;
        }
    }
    if (event.type == sf::Event::TextEntered && event.key.code != sf::Keyboard::BackSpace)
    {
        if (event.text.unicode < 128)
        {
            m_wantToSend += static_cast<char>(event.text.unicode); // on recupere les caracteres entré par l'utilisateur
            chatBoxText.setString(m_wantToSend);
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
