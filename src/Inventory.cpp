#include "../include/Inventory.hpp"
#include "../include/Personnage.hpp"
using namespace std;

Inventory::Inventory()
{
    m_inventory.resize(10);
    for(unsigned int i =0; i < m_inventory.size(); i++)
        for(int j=0; j<6; j++)
            m_inventory[i].push_back(new Item());
    m_itemHand = new Item();
    m_isItemHand = false;

    m_inventoryTemp.resize(10);
    for(unsigned int i =0; i < m_inventoryTemp.size(); i++)
        for(int j=0; j<6; j++)
            m_inventoryTemp[i].push_back(new Item());
}
void Inventory::init(Personnage *perso)
{
    m_open = false;
    hotBar.setOrigin(0, 0);
    m_sizeSlot = 128;
    m_slotsX = 10;
    m_slotsY = 6;
    m_personnage = perso;
    ressourcesBox = m_personnage->getGSys();

    textureInv = ressourcesBox->requestTexture("ressources/inventoryPatern.png");
    textureHot = ressourcesBox->requestTexture("ressources/toolBar.png");
    textureSlot = ressourcesBox->requestTexture("ressources/select.png");
    patern.setPosition(m_patternXPos,m_patternYPos);
    patern.setTexture(*textureInv);

    hotBar.setPosition(m_patternXPos,m_patternYPos);
    hotBar.setTexture(*textureHot);

    slotSelect.setTexture(*textureSlot);
    m_itemFont = ressourcesBox->requestFont("arial.ttf");
    m_slotSelected = 0;

    for(int i=0; i<9; i++)
    {
        m_itemTexture[i] = ressourcesBox->requestTexture("tileset.png",sf::IntRect(32*i,0,32,32));
    }
    for(unsigned int i = 0; i < m_inventory.size(); i++)
    {
        for(unsigned int j = 0; j < m_inventory[0].size(); j++)
        {
            m_inventory[i][j]->setTexture(m_itemTexture[m_inventory[i][j]->getID()]);
            m_inventory[i][j]->setPolice(m_itemFont);
            m_inventoryTemp[i][j]->setPolice(m_itemFont);
        }
    }
    m_blocked = false;
    m_itemHand->setPolice(m_itemFont);
}
bool Inventory::click(sf::Vector2i mousePos,int t_click)
{
    //on recupere le slot clicker
    int posX = (float(mousePos.x) / m_sizeSlot)*3;
    int posY = (float(mousePos.y) / m_sizeSlot)*3;
    if(posX>=0 && posX<=9 && posY>=0 && posY <= 5)//on verifie si le slot est pas en dehors de l'inventaire
    {
        if(!m_isItemHand && m_inventory[posX][posY]->getQty()>0 && !m_blocked && t_click) // verifie si tu as pas déja un item dans la main && si la qty est superieur a zero && sa block pour evité que sa clignote && que c'est un click gauche
        {
            m_isItemHand = true;
            //copy les options importante de l'item qui est dans l'inventaire vers la main
            m_itemHand->setQty(m_inventory[posX][posY]->getQty());
            m_itemHand->setID(m_inventory[posX][posY]->getID());
            m_itemHand->setTexture(m_itemTexture[m_inventory[posX][posY]->getID()]);
            //vide le slot de l'inventaire
            m_inventory[posX][posY]->setQty(0);
            m_inventory[posX][posY]->setID(0);
            m_inventory[posX][posY]->setTexture(m_itemTexture[0]);
        }
        else if(!m_isItemHand && m_inventory[posX][posY]->getQty()>0 && !m_blocked && !t_click) // les meme verif juste que c'est avec le click droit
        {
            if(int(m_inventory[posX][posY]->getQty()/2)>0) // verifie si quand tu en prend la moitié cela retourne un > a 0
            {
                m_isItemHand = true;
            }
            //copy la moitié de la quantity de l'item de l'inventaire vers la main
            m_itemHand->setQty(int(m_inventory[posX][posY]->getQty()/2));
            m_itemHand->setID(m_inventory[posX][posY]->getID());
            m_itemHand->setTexture(m_itemTexture[m_inventory[posX][posY]->getID()]);
            //enleve la quantité recuperer de l'inventaire
            m_inventory[posX][posY]->takeQty(int(m_inventory[posX][posY]->getQty()/2));
        }
        else if(m_isItemHand && !m_blocked && t_click) // verifie si tu as un item dans la main && un click gauche
        {
            if(m_inventory[posX][posY]->getQtyRestante()>=m_itemHand->getQty() && (m_itemHand->getID() == m_inventory[posX][posY]->getID() || m_inventory[posX][posY]->getID() == 0)) //verifie si ya de la place && que c'est du meme type ou que c'est vide
            {
                //copy les item present dans la main et le met dans le slot de l'inventaire
                m_inventory[posX][posY]->addItem(m_itemHand->getQty());
                m_inventory[posX][posY]->setID(m_itemHand->getID());
                m_inventory[posX][posY]->setTexture(m_itemTexture[m_itemHand->getID()]);
                //vide ce que contient la main
                m_itemHand->setQty(0);
                m_itemHand->setID(0);
                m_itemHand->setTexture(m_itemTexture[0]);
                m_isItemHand = false;
            }
            else if(m_inventory[posX][posY]->getQtyRestante()<m_itemHand->getQty() && m_itemHand->getID() == m_inventory[posX][posY]->getID()) //verifie si ya plus de place && que c'est du meme type
            {

                int nbrItemaRajouter = m_inventory[posX][posY]->getQtyRestante(); // on regarde combien il y a de place restante
                // on remplie donc le slot de l'inventaire
                m_inventory[posX][posY]->addItem(nbrItemaRajouter);
                m_inventory[posX][posY]->setID(m_itemHand->getID());
                m_inventory[posX][posY]->setTexture(m_itemTexture[m_itemHand->getID()]);
                //on eleve ce qu'on a rajouter dans la quantité que contient la main
                m_itemHand->takeQty(nbrItemaRajouter);
                if(m_itemHand->getQty()==0) //si elle est vide on dit qu'elle ne contient plus d'item
                    m_isItemHand = false;
            }
            else if (m_itemHand->getID() != m_inventory[posX][posY]->getID()) // verifie si l'item dans la main est different de l'item ou on veut poser
            {
                //copy les option importante de l'item de la main qu'on stock en ram
                int tempQty = m_itemHand->getQty();
                int tempID = m_itemHand->getID();
                //on met dans la main ce que contient l'inventaire
                m_itemHand->setQty(m_inventory[posX][posY]->getQty());
                m_itemHand->setID(m_inventory[posX][posY]->getID());
                m_itemHand->setTexture(m_itemTexture[m_inventory[posX][posY]->getID()]);
                //on met dans l'inventaire ce que contener la main stocker en ram
                m_inventory[posX][posY]->setQty(tempQty);
                m_inventory[posX][posY]->setID(tempID);
                m_inventory[posX][posY]->setTexture(m_itemTexture[tempID]);
            }
        }
        else if(m_isItemHand && !m_blocked && !t_click) // verifie si tu as un item dans la main && un click droit
        {
            if(m_inventory[posX][posY]->getQtyRestante()>=1 && (m_itemHand->getID() == m_inventory[posX][posY]->getID() || m_inventory[posX][posY]->getID() == 0)) //verifie si ya de la place && que c'est du meme type ou que c'est vide
            {
                //on augmente le nombre d'item de 1 dans l'inventaire
                m_inventory[posX][posY]->addItem(1);
                m_inventory[posX][posY]->setID(m_itemHand->getID());
                m_inventory[posX][posY]->setTexture(m_itemTexture[m_itemHand->getID()]);
                //on eleve 1 dans la quantité que contient la main
                m_itemHand->takeQty(1);
                if(m_itemHand->getQty()==0) //si elle est vide on dit qu'elle ne contient plus d'item
                    m_isItemHand = false;
            }
        }
        return true;
    }
    return false;
}
bool Inventory::addItem(Item item)
{
    for(int j=0; j < m_slotsY; ++j)
    {
        for(int i=0; i < m_slotsX; ++i)
        {
            if(m_inventory[i][j]->getID() == item.getID())
            {
                if(m_inventory[i][j]->getQtyRestante()>=item.getQty())
                {
                    m_inventory[i][j]->addItem(item.getQty());
                    return true;
                }
                else
                {
                   m_inventory[i][j]->addItem(m_inventory[i][j]->getQtyRestante());
                   item.takeQty(m_inventory[i][j]->getQtyRestante());
                }
            }
        }
    }
    for(int j=0; j < m_slotsY; ++j)
    {
        for(int i=0; i < m_slotsX; ++i)
        {
            if(m_inventory[i][j]->getQty() == 0)
            {
                m_inventory[i][j]->setQty(item.getQty());
                m_inventory[i][j]->setName(item.getName());
                m_inventory[i][j]->setID(item.getID());
                m_inventory[i][j]->setTexture(m_itemTexture[item.getID()]);
                return true;
            }
            else if(m_inventory[i][j]->getID() == item.getID())
            {
                if(m_inventory[i][j]->getQtyRestante()>=item.getQty())
                {
                    m_inventory[i][j]->addItem(item.getQty());
                    return true;
                }
                else
                {
                   m_inventory[i][j]->addItem(m_inventory[i][j]->getQtyRestante());
                   item.takeQty(m_inventory[i][j]->getQtyRestante());
                }
            }
        }
    }
    return true;
}
void Inventory::open()
{
    if(m_open)
    {
        m_open = false;
        m_personnage->setCanMine(true);
    }
    else
    {
        m_open = true;
        m_personnage->setCanMine(false);
    }
}
void Inventory::render(int x, int y)
{
    sf::RenderWindow& mWindow = Window::getWindow();
    hotBar.setPosition(x+10,y);
    patern.setPosition(x+10,y+m_sizeSlot);
    mWindow.draw(hotBar);
    if(m_open)
    {
        mWindow.draw(patern);

        for(int j=1; j < m_slotsY; ++j)
        {
            for(int i=0; i < m_slotsX; ++i)
            {
                if(m_inventory[i][j]->getQty() > 0)
                {
                    m_inventory[i][j]->render(x+16+i*m_sizeSlot+15,y+16+m_sizeSlot+(j-1)*m_sizeSlot+15);
                }
            }
        }
    }
    for(int i=0; i < m_slotsX; ++i)
    {
        if(m_inventory[i][0]->getQty() > 0)
            m_inventory[i][0]->render(x+16+i*m_sizeSlot+15,y+16+15);
    }
    slotSelect.setPosition(x+m_sizeSlot*m_slotSelected,y);
    mWindow.draw(slotSelect);
    m_patternXPos = x;
    m_patternYPos = y;
    if(m_isItemHand)
    {
        sf::Vector2i MousePos = sf::Mouse::getPosition(mWindow);
        sf::Vector2f MousePosCoof = mWindow.mapPixelToCoords(MousePos);
        m_itemHand->render(int(MousePosCoof.x),int(MousePosCoof.y));
    }
}
bool Inventory::getOpen()
{
    return m_open;
}

void Inventory::disp()
{
    for(int j=0; j < 1; ++j)
    {
        for(int i=0; i < 3; ++i)
        {
            cout<<"Mon slot : "<<i<<"-"<<j<<" contient : "<<endl;
            m_inventory[i][j]->disp();
        }
    }
    cout<<"Mon slot : "<<9<<"-"<<4<<" contient : "<<endl;
    m_inventory[9][5]->disp();
}

void Inventory::selectSlot(int slot)
{
    m_slotSelected = slot;
}

int Inventory::getIDSelectSlot()
{
    if(m_inventory[m_slotSelected][0]->getQty()==0)
    {
        m_inventory[m_slotSelected][0]->setName("Air");
        m_inventory[m_slotSelected][0]->setID(0);
        return 0;
    }
    else
        return m_inventory[m_slotSelected][0]->getID();
}
void Inventory::removeQTY()
{
    m_inventory[m_slotSelected][0]->removeQty(1);
}
void Inventory::save(string m_nomMap)
{
    ofstream inv;
    ostringstream convPathFichier;
    convPathFichier << "maps\\" << m_nomMap << "\\inv.data"; // conversion du j en string
    string newPathFichier;
    newPathFichier = convPathFichier.str();
    inv.open(newPathFichier.c_str());
    if(inv)
    {
        for(unsigned int i = 0; i < m_inventory.size(); i++)
        {
            for(unsigned int j = 0; j < m_inventory[0].size(); j++)
            {
                inv <<m_inventory[i][j]->getID()<< " "<<m_inventory[i][j]->getQty()<<" ";
            }
            inv <<endl;
        }
    }
    inv.close();
}

void Inventory::load(string m_nomMap)
{
    ifstream inv;
    ostringstream convPathFichier;
    convPathFichier << "maps\\" << m_nomMap << "\\inv.data"; // conversion du j en string
    string newPathFichier;
    newPathFichier = convPathFichier.str();
    inv.open(newPathFichier.c_str());
    if(inv)
    {
        for(unsigned int i = 0; i < m_inventory.size(); i++)
        {
            for(unsigned int j = 0; j < m_inventory[0].size(); j++)
            {
                int tempID = 0;
                inv >> tempID;
                m_inventory[i][j]->setID(tempID);
                int tempQty = 0;
                inv >> tempQty;
                m_inventory[i][j]->setQty(tempQty);
            }
        }
    }
    inv.close();
}
int Inventory::getSelectSlot()
{
    return m_slotSelected;
}
void Inventory::setBlocked(bool t_blocked)
{
    m_blocked = t_blocked;
}
void Inventory::trie()
{
    for(unsigned int i = 0; i < m_inventory.size(); i++)
    {
        for(unsigned int j = 0; j < m_inventory[0].size(); j++)
        {
            m_inventoryTemp[i][j]->copyItem(m_inventory[i][j]);
            m_inventoryTemp[i][j]->setTexture(m_itemTexture[m_inventory[i][j]->getID()]);
        }
    }
    int tempK = 0;
    int tempL = 0;
    for(unsigned int j = 1; j < m_inventory[0].size(); j++)
    {
        for(unsigned int i = 0; i < m_inventory.size(); i++)
        {
            int plusPetitID = 100;
            for(unsigned int l = 1; l < m_inventory[0].size(); l++)
            {
                for(unsigned int k = 0; k < m_inventory.size(); k++)
                {
                    if(m_inventoryTemp[k][l]->getID()<plusPetitID && m_inventoryTemp[k][l]->getID()>0)
                    {
                        plusPetitID = m_inventoryTemp[k][l]->getID();
                        tempK = k;
                        tempL = l;
                    }

                }
            }
            m_inventory[i][j]->setTexture(m_itemTexture[0]);
            m_inventory[i][j]->setID(0);
            m_inventory[i][j]->setQty(0);
            if(m_inventoryTemp[tempK][tempL]->getID()>0)
            {
                m_inventory[i][j]->copyItem(m_inventoryTemp[tempK][tempL]);
                m_inventory[i][j]->setTexture(m_itemTexture[m_inventoryTemp[tempK][tempL]->getID()]);

            }
            m_inventoryTemp[tempK][tempL]->setID(0);
        }
    }
}
bool Inventory::getIsItemHand()
{
    return m_isItemHand;
}
Item* Inventory::getItem()
{
    m_isItemHand = false;
    return m_itemHand;
}
