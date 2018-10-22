#include "../include/Personnage.hpp"
#include "../include/World.hpp"
#include "../include/Level.hpp"

using namespace std;

Personnage::Personnage(World* t_world, GlobalSys* t_ressourceBox) : Entity(t_world,t_ressourceBox)
{
    m_sprite.setPosition(100,980*32);
    posView.x = 10;
    posView.y = 10;
    viewWindow.reset(sf::FloatRect(0,0,64*32,64*32));
    //gauche base 16 = Q
    m_control[0] = 16;
    //droite base 3 = D
    m_control[1] = 3;
    //saut 57 = space
    m_control[2] = 57;
    //inventory 8 = I
    m_control[3] = 8;
    //reset 17 = R
    m_control[4] = 17;
    //save base 18 = S
    m_control[5] = 18;
    //retrie inv 15 = P
    m_control[6] = 15;
}

void Personnage::init()
{
    inventaire.init(this);
    m_version.setString("Aerria V3.1-INDEV");
    m_version.setCharacterSize(50);
    m_version.setColor(sf::Color::White);
    m_version.setFont(*m_ressourceBox->requestFont("arial.ttf"));
    int tempp = 0;
    for(int j=0; j<2; j++)
        for(int i=0; i<5; i++)
        {
            m_texture[tempp] = m_ressourceBox->requestTexture("ressources/personnage.png", sf::IntRect(i * 64, j * 96, 64, 96));
            tempp++;
        }
    m_pos = sf::Vector2f(100*32,980*32);
    m_speed = 0.5;
    m_maxSpeed = 100;
    m_hitbox.init(this,sf::Vector2f(34,93));

    m_level = m_world->getLevel();
    loadRegion();
    pioche.setOutils(3);
    m_deplacement.x = 0;
    m_deplacement.y = 0;
    m_depLeft = false;
    m_depRight = false;
    m_jump = false;
    m_inventory = false;
    m_invIsOpen = false;
    m_reset = false;
    m_trieInv = false;
    m_click = false;
    decoupAnim(0);
    m_animCount = 0;
    tempAnim = 0;
    m_puissJump = 30;
    m_porteeMiningBlock = 9999;
    m_canMine = true;
}
void Personnage::render()
{
    sf::RenderWindow& mWindow = Window::getWindow();
    if(m_pos.x+(32*32) > m_level->getLargeur()*32-100 || m_pos.x-(32*32) < 100);
    else
        posView.x = int(m_pos.x-(mWindow.getSize().x*3/2));
    if(m_pos.y+(32*32) > m_level->getHauteur()*32-100 || m_pos.y-(32*32) < 100);
    else
        posView.y = int(m_pos.y-(mWindow.getSize().y*3/2));
    viewWindow.reset(sf::FloatRect(posView.x,posView.y,mWindow.getSize().x*3,mWindow.getSize().y*3));
    mWindow.setView(viewWindow);
    m_sprite.setPosition(m_pos.x,m_pos.y);
    mWindow.draw(m_sprite);
    inventaire.render(posView.x+2, posView.y+2);
    m_version.setPosition((posView.x+mWindow.getSize().x*3)-600,(posView.y+mWindow.getSize().y*3)-50);
    mWindow.draw(m_version);
}
void Personnage::update()
{
    m_numRegionPerso = regionPerso();
    processGravity();
    acceleration();
    Move();
    if((m_numRegionPerso.x != regionPerso().x) || (m_numRegionPerso.y != regionPerso().y))
    {
        loadMap();
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        clicked(1);
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        clicked(0);
    }
}
void Personnage::acceleration()
{
    if(m_depLeft && !m_depRight)
    {
        if(m_deplacement.x > m_maxSpeed*-1)
            m_deplacement.x -= m_speed;
    }
    else if(m_depRight && !m_depLeft)
    {
        if(m_deplacement.x < m_maxSpeed)
            m_deplacement.x += m_speed;
    }
    else
        m_deplacement.x = 0;
}
void Personnage::handlePlayerInput(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == m_control[0])
        {
            m_depLeft = true;
        }
        else if (event.key.code == m_control[1])
        {
            m_depRight = true;
        }
        else if(event.key.code == m_control[2])
        {
            if(!m_jump && m_toucheSol)
            {
                m_deplacement.y -= m_puissJump;
                m_jump = true;
            }
        }
        else if(event.key.code == m_control[3])
        {
            if(!m_inventory)
            {
                m_inventory = true;
                inventaire.open();
            }
        }
        else if(event.key.code == m_control[4])
        {
            if(!m_reset)
            {
                m_reset = true;
                Entity::setPosition(100*32,980*32);
                loadMap();
            }
        }
        else if(event.key.code == m_control[5])
        {
            m_level->save();
        }
        else if (event.key.code == m_control[6])
        {
            if(!m_trieInv)
            {
                inventaire.trie();
                m_trieInv = true;
            }
        }
        else
            for(int i = 0; i<=9; i++)
                if(event.key.code == i+26)
                    if(i!=0)
                    {
                        inventaire.selectSlot(i-1);
                    }
                    else
                    {
                        inventaire.selectSlot(9);
                    }
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == m_control[0])
        {
            m_depLeft = false;
        }
        else if (event.key.code == m_control[1])
        {
            m_depRight = false;
        }
        else if(event.key.code == m_control[2])
        {
            m_jump = false;
        }
        else if(event.key.code == m_control[3])
        {
            m_inventory = false;
        }
        else if(event.key.code == m_control[4])
        {
            m_reset = false;
        }
        else if (event.key.code == m_control[6])
        {
            m_trieInv = false;
        }
    }
    else if (event.type == sf::Event::MouseWheelMoved)
    {
        int i = inventaire.getSelectSlot();
        i = event.mouseWheel.delta + i;
        if(i>9)i-=10;
        if(i<0)i+=10;
        inventaire.selectSlot(i);
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        m_click = true;
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        inventaire.setBlocked(false);
        m_click = false;
    }
}
void Personnage::Move()
{
    m_pos.x += m_deplacement.x;
    if(m_deplacement.x > 0)
        decoupAnim(int(m_animCount));
    if(m_deplacement.x < 0)
    {
        decoupAnim(5+int(m_animCount));
        tempAnim = 1;
    }
    if(m_deplacement.x == 0)
    {
        if(tempAnim==1)
            m_animCount = 5;
        else
            m_animCount = 0;
        decoupAnim(m_animCount);
    }
    m_animCount+=0.1;
    if(m_animCount>4) m_animCount=0;
    if(!checkCollision() || m_pos.x > m_world->getLevel()->getLargeur()*32-200 || m_pos.x < 116)
    {
        m_pos.x -= m_deplacement.x;
        m_deplacement.x = 0;
    }
    m_pos.y += m_deplacement.y;
    if(!checkCollision() || m_pos.y > m_world->getLevel()->getHauteur()*32-200 || m_pos.y < 116)
    {
        m_pos.y -= m_deplacement.y;
        m_deplacement.y = 0;
        m_toucheSol = true;
    }
    else
    {
        m_toucheSol = false;
    }
}
void Personnage::loadMap()
{
    loadRegion();
    unloadRegion();
}
void Personnage::clicked(int click)
{

    sf::RenderWindow& mWindow = Window::getWindow();

    //determine sur quel block tu as clicker
    sf::Vector2i MousePos = sf::Mouse::getPosition(mWindow);
    sf::Vector2f MousePosCoof = mWindow.mapPixelToCoords(MousePos);
    sf::Vector2i MousePosCoo;
    MousePosCoo.x = int(MousePosCoof.x/32);
    MousePosCoo.y = int(MousePosCoof.y/32);
    if(inventaire.getOpen()) // si l'inventaire est ouvert
    {
        if(inventaire.click(MousePos,click)) // Si tu click dans l'inventaire
            m_canMine = false; // interdit de miner
        else
            m_canMine = true; // sinon autorise de miner
    }
    inventaire.setBlocked(true);
    if(m_canMine) // verifie si le perso a l'autorisation de miner
    {
        if(MousePosCoo.x >= 20 &&  MousePosCoo.y >= 20 && MousePosCoo.x <= m_level->getLargeur()-20 &&  MousePosCoo.y <= m_level->getHauteur()-20) // verifie si le block clicker n'est pas hors map
        {
            sf::Vector2i regionBlockClicker = sf::Vector2i(MousePosCoo.x/256,MousePosCoo.y/256);
            sf::Vector2i blockClicker = sf::Vector2i(MousePosCoo.x%256,MousePosCoo.y%256);
            Region* test = m_world->getLevel()->getRegion(regionBlockClicker);
            if(inventaire.getIsItemHand())
            {
                Entity* itemBreak = new DropedItem(m_world,m_ressourceBox,*inventaire.getItem());
                itemBreak->setPosition((int((m_pos.x+200)/32)*32),m_pos.y+10);
                test->creerEntity(itemBreak);
                inventaire.getItem()->setID(0);
                inventaire.getItem()->setQty(0);

            }
            if(m_pos.x-m_porteeMiningBlock*32 < MousePosCoof.x && m_pos.x+m_porteeMiningBlock*32 > MousePosCoof.x && m_pos.y-m_porteeMiningBlock*32 < MousePosCoof.y && m_pos.y+m_porteeMiningBlock*32 > MousePosCoof.y) //Verifie si la portée de minage est suffisante
            {
                if(click) // if(iteminhand est de type outils)
                {
                    if(miningBlock.getTiles() != test->getBlock(blockClicker)) // si le block est different que le precedant on rebuild le nouveau sinon on garde l'ancien
                        miningBlock.setBlock(test->getBlock(blockClicker));
                    if(miningBlock.getMine()) // esque le block est minable ?
                    {
                        if(mining.getElapsedTime().asSeconds() >= pioche.getVitesse()) //j'attend le cd pour miner le block
                        {
                            //je restart le compteur et j'inflige des degats au block

                            mining.restart();
                            if(miningBlock.damage(pioche.getPuissance())) // esque le block est cassé avec les degats infligé si oui je le transforme en air
                            {
                                test->setBlock(blockClicker,0);
                                Item temp(miningBlock.getTiles(),64,1,block,miningBlock.getName());
                                Entity* itemBreak = new DropedItem(m_world,m_ressourceBox,temp);
                                itemBreak->setPosition((int(MousePosCoof.x/32)*32)+8,int(MousePosCoof.y/32)*32);
                                test->creerEntity(itemBreak);
                            }
                        }
                    }
                }
                else if(1) // else is (iteminhand est de type block posable)
                {
                    miningBlock.setBlock(test->getBlocks()[blockClicker.x][blockClicker.y]);
                    if(miningBlock.getTiles() == 0) //on verifie que on veut poser un block sur un endroit vide
                    {
                        int IDBlockInHand = inventaire.getIDSelectSlot(); // on recupere l'id du block dans la main
                        test->setBlock(blockClicker,IDBlockInHand); // on met le block
                        if(!checkCollision()) // on verifie que ya pas de colision avec joueur
                        {
                            test->setBlock(blockClicker,0); //si collision on remet de l'air
                        }
                        else
                            inventaire.removeQTY();
                    }
                }
            }
        }
    }
}
void Personnage::loadRegion()
{
    string tilesetTexture = "tileset.png";
    sf::Vector2i regionALoad;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            regionALoad.x = regionPerso().x+i-1;
            regionALoad.y = regionPerso().y+j-1;
            if(regionALoad.x >= 0 && regionALoad.y >= 0 && regionALoad.x < m_level->getVecRegion().x && regionALoad.y < m_level->getVecRegion().y)
            {
                m_level->getRegion(regionALoad)->loadTileMap();
            }
            else
            {
                //pas de load region hors map
            }
        }
    }
}

void Personnage::unloadRegion()
{
    sf::Vector2i nbrRegion = m_level->getVecRegion();
    for(int i = 0; i<nbrRegion.x; i++)
        for(int j = 0; j<nbrRegion.y; j++)
        {
            if(i >= regionPerso().x-1 && i <= regionPerso().x+1 && j >= regionPerso().y-1 && j <= regionPerso().y+1);
            else
                m_level->getRegion(sf::Vector2i(i,j))->unload();
        }

}
sf::Vector2i Personnage::regionPerso()
{
    sf::Vector2i numRegion;
    numRegion.x = int(m_pos.x/(m_level->getDivision()*32));
    numRegion.y = int(m_pos.y/(m_level->getDivision()*32));
    return numRegion;
}
void Personnage::decoupAnim(int state)
{
    m_sprite.setTexture(*m_texture[state]);
}

Inventory Personnage::getInventory()
{
    return inventaire;
}

void Personnage::save(string m_nomMap)
{
    inventaire.save(m_nomMap);
}

void Personnage::load(string m_nomMap)
{
    inventaire.load(m_nomMap);
}
void Personnage::setCanMine(bool t_canMine)
{
    m_canMine = t_canMine;
}
bool Personnage::getClicked()
{
    return m_click;
}
