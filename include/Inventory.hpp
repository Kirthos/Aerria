#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Item.hpp"
#include "SingletonWindow.h"
#include <fstream>
#include <sstream>
#include "GlobalSys.hpp"

class Personnage;
class Inventory
{
public:
    Inventory();
    void init(Personnage *perso);
    void update(sf::Vector2f *mousePosCoo); // doit etre executer pour permettre au joueur de deplacer les items manuelement
    Item* drop(); //même chose que pour la fonction addItem ... en tout cas ca renverra l'item, et le deletera enfin a voir si ca le sauvegarde dans un tableau propre a l'inventaire.En fait faudrais stocker tout les item dans un seul endroit du PRGM
    bool addItem(Item item); // a voir si ce sera un pointeur ou une copie en fonction de la gestion des item au sol et tout ... a voir. En fait faudrais stocker tout les item dans un seul endroit du PRGM. Renvoi false si plus de place ou autre erreur.
    void invClear(); // delete tout l'inventaire (j'ai eu du mal a trouver le nom)
    bool checkForItem(Item itemLooked, int QtyLooked); // je vous laisse deviner l'utilité (true = avaible / false = unavaible)
    bool removeItem(); // je vous conseil d'utiliser ca aprés avoir check si l'item est disponible, mais renvera tout de même false si l'item ne peut pas être supprimer
    std::vector<std::vector<Item> > getInvMap(); // a utiliser avec mon aide, sauf si vous comprenez comment ca marche, explication pour les slot speciaux a venir
    void setPersonnage(Personnage* persoPTR); // defini le personnage propriétaire de l'inventaire
    Personnage* getPersonnage();
    Item* itemInHand();

    bool click(sf::Vector2i mousePos,int t_click);
    void render(int x, int y);
    void open();
    bool getOpen();
    void selectSlot(int slot);
    int getIDSelectSlot();
    void save(std::string m_nomMap);
    void load(std::string m_nomMap);
    int getSelectSlot();
    void removeQTY();
    sf::Texture* getTextureByID(int id);
    void setBlocked(bool t_blocked);
    void trie();
    bool getIsItemHand();
    Item* getItem();
protected:
    sf::Texture* textureInv;
    sf::Texture* textureHot;
    sf::Texture* textureSlot;
    sf::Sprite patern;
    sf::Sprite hotBar;
    sf::Sprite slotSelect;

    sf::RenderWindow* mWindow;
private:

    int m_slotsX;
    int m_slotsY;
    std::vector<std::vector<Item*> > m_inventory;
    std::vector<std::vector<Item*> > m_inventoryTemp;
    int m_patternXPos;
    int m_patternYPos;
    bool m_open;
    int m_sizeSlot;

    Personnage* m_personnage;

    void disp();
    int m_slotSelected;
    GlobalSys *ressourcesBox;
    sf::Texture* m_itemTexture[9];
    sf::Font* m_itemFont;

    Item* m_itemHand;
    bool m_isItemHand;
    bool m_blocked;
};

#endif // INVENTORY_H_INCLUDED
