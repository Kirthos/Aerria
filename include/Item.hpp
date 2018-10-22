#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include <iostream>
#include "SingletonWindow.h"

class DropedItem;

enum itemType {block, usable, armor, equipable};

struct itemProperties
{
    int m_maxQty;
    int m_qty;
    itemType m_type;
    std::string m_name;
    bool infiniteState;
};

class Item
{
public:
    Item(        int t_ID,
                 int t_maxQty,
                 int t_qty,
                 itemType t_type,
                 std::string t_name); // constructeur a la con, sera remplacer par une struct properties plus tard, pas s'en occuper pour l'instant, ce sera plus facile a utiliser plus tard
    Item(itemProperties t_parameter);
    Item();
    void setProperties(itemProperties t_properties);
    itemProperties getProperties();
    DropedItem drop(); // renvoi l'item dropé, attention, l'item est alors mis a la QTY 0 (properties supremier, name mis a "VoidItem"), a vous de l'enlever de la grille ou il est stocker, de le delete, ou de lui mettre une QTY nouvelle
    Item getItem(); // renvoi une cpy de l'item !!!!!!
    int setQty(int t_Qty); //Defini la quantité, renvoi un int diferent de 0 equivalent a la quantity d'item qui ne peuvent etre ajouter (stack plein), ou renverra un negatif correspondant a cb la demande est en dessous de 0, [ATTENTION] Mais fait comme même l'operation !!!
    Item takeQty(int t_Qty); //retourne le même item avec une qty indiquer, attention car ca enleve cette quantity a l'item sources, renverra un negatif equivalent au nombre manquant d'item
    int addItem(int t_Qty); // ajoute des items et renvoi un int different de 0 si on essai de donenr plus d'item que autoriser
    void removeQty(int t_Qty); //enleve des item, sans generer un nouveau item, aussi, block a 0 sans generer d'erreur si la qty enlever est trop grande
    int getQty();
    void deleteItem(); // fait un delete(This)
    void setInfinite(bool t_infinite); // defini si la quantity du stack de l'item peut etre differente de son maximum
    bool isInfinite(); // pas besoin d'expliquer si ?
    void disp();
    int getID();
    void setID(int id);
    std::string getName();
    void setName(std::string name);
    void render(int x,int y);
    void setTexture(sf::Texture* t_texture);
    void setPolice(sf::Font* t_font);
    sf::Texture* getTexture();
    int getQtyRestante();
    void copyItem(Item* t_item);
protected:
    int m_ID;
    int m_maxQty;
    int m_qty;
    itemType m_type;
    itemProperties m_properties;
    std::string m_name;
    std::string m_iconPath;
    bool infiniteState;
    sf::Sprite m_sprite;
    sf::Texture *m_texture;
    sf::Text m_textQty;
    sf::Font *m_font;
private:
};

#endif // ITEM_H
