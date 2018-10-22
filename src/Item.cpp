#include "../include/Item.hpp"
using namespace std;

Item::Item()
{
    m_maxQty = 100;
    m_qty = 0;
    m_name = "Air";
    m_iconPath = "ressources/stone.png";
    m_ID = 0;
    stringstream ss;
    ss << m_qty;
    string str = ss.str();
    m_textQty.setString("18");
    m_textQty.setCharacterSize(50);
    m_textQty.setColor(sf::Color::White);
}

Item::Item(int t_ID,
           int t_maxQty,
           int t_qty,
           itemType t_type,
           std::string t_name)
{
    m_maxQty = t_maxQty;
    m_qty = t_qty;
    m_name = t_name;
    m_ID = t_ID;
    stringstream ss;
    ss << m_qty;
    string str = ss.str();
    m_textQty.setString(str);
    m_textQty.setCharacterSize(50);
    m_textQty.setColor(sf::Color::White);
}

int Item::getID()
{
    return m_ID;
}

Item::Item(itemProperties t_parameter)
{
    m_maxQty = t_parameter.m_maxQty;
    m_qty = t_parameter.m_qty;
    m_name = t_parameter.m_name;
    std::string m_name = t_parameter.m_name;
}

void Item::removeQty(int t_Qty)
{
    if(!infiniteState)
    {
        if (m_qty - t_Qty < 0)
        {
            m_qty = 0;
        }
        else
            m_qty -= t_Qty;
    }
}
Item Item::getItem()
{
    return (*this);
}
int Item::setQty(int t_Qty)
{
    if (t_Qty > m_maxQty)
    {
        m_qty = m_maxQty;
        return (t_Qty - m_maxQty);
    }
    else if (t_Qty < 0)
    {
        m_qty = 0;
        return (m_qty);
    }
    else
    {
        m_qty = t_Qty;
        return (0);
    }
}
int Item::getQty()
{
    return m_qty;
}
int Item::addItem(int t_Qty)
{
    if (t_Qty < (m_maxQty - m_qty))
    {
        m_qty += t_Qty;
        return (0);
    }
    else
    {
        int tempVar = m_maxQty - m_qty;
        m_qty += tempVar;
        t_Qty -= tempVar;
        return (t_Qty);
    }

}
Item Item::takeQty(int t_Qty)
{
    Item* returnValue;
    returnValue = new Item(m_properties);
    if (m_qty - t_Qty >= 0)
    {
        m_qty -= t_Qty;
        returnValue->setQty(t_Qty);
    }
    else
    {
        returnValue->setQty(0);
    }
    return (*returnValue);
}
void Item::disp()
{
    std::cout << "qty : " << m_qty << "/" << m_maxQty << " \n";
    std::cout << "name : " << m_name << " \n";
//    std::cout << "sinon je suis du type " << m_type << " ... BYE";
//    std::cout << std::endl;
    std::cout << std::endl;
}

void Item::render(int x,int y)
{
    sf::RenderWindow& mWindow = Window::getWindow();
    stringstream ss;
    ss << m_qty;
    string str = ss.str();
    m_textQty.setString(str);
    m_sprite.setPosition(x,y);
    m_textQty.setPosition(x+25,y+55);
    mWindow.draw(m_sprite);
    mWindow.draw(m_textQty);
}

std::string Item::getName()
{
    return m_name;
}
void Item::setName(std::string name)
{
    m_name = name;
}
void Item::setID(int id)
{
    m_ID = id;
}
void Item::setTexture(sf::Texture* t_texture)
{
    m_sprite.setTexture(*t_texture);
    m_sprite.setScale(2,2);
}
void Item::setPolice(sf::Font *t_font)
{
    m_textQty.setFont(*t_font);
}
sf::Texture* Item::getTexture()
{
    return m_texture;
}
int Item::getQtyRestante()
{
    return (m_maxQty-m_qty);
}
void Item::copyItem(Item* t_item)
{
    m_qty = t_item->getQty();
    m_ID = t_item->getID();
}
