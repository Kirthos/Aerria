#include "../include/GlobalSys.hpp"
#include "World.hpp"

GlobalSys::GlobalSys()
{
    preload(); //preload les ressources, la fonction en question est tout en bas, vous avez juste a faire une request normal sans recuperer la valeur de return
}

void GlobalSys::giveWorld(World* t_world)
{
    m_world = t_world;
    m_level = m_world->getLevel();
}

void GlobalSys::fillCircle(sf::Vector2f t_pos, int rad, int type)
{
    for (int i = -rad*32; i <= rad*32 ; i += 32)
    {
        for (int j = -rad*32 ; j<= rad*32; j += 32)
        {
            if (calculateDistance(sf::Vector2f(t_pos.x+i, t_pos.y+j), t_pos) < rad*32)
                m_level->setBlock(sf::Vector2i(t_pos.x+i, t_pos.y+j), type);
        }
    }
}
void GlobalSys::fillSquare(sf::Vector2f t_pos, int rad, int type)
{
    for (int i = -rad*32; i <= rad*32 ; i += 32)
    {
        for (int j = -rad*32 ; j<= rad*32; j += 32)
        {
            m_level->setBlock(sf::Vector2i(t_pos.x+i, t_pos.y+j), type);

        }
    }
}

void GlobalSys::setBlock(sf::Vector2f t_pos, int type)
{
    m_level->setBlock(sf::Vector2i(t_pos), type);
}
int GlobalSys::getBlock(sf::Vector2f t_pos)
{
    m_level->getBlock(sf::Vector2i(t_pos));
}
































World* GlobalSys::getWorld()
{
    return m_world;
}
float GlobalSys::calculateDistance(sf::Vector2f pt1, sf::Vector2f pt2)
{
    return (sqrt((pt1.x-pt2.x)*(pt1.x-pt2.x)+(-(pt2.y)-(-(pt1.y)))*(-(pt2.y)-(-(pt1.y)))));
}





sf::Texture* GlobalSys::requestTexture(std::string t_requestName, sf::IntRect t_dimension)
{
    ressType type = imgPart;
    std::string nameNeedForLoad = t_requestName;
    t_requestName+='§';
    std::stringstream ss;
    ss << t_dimension.left << '§' << t_dimension.top << '§' << t_dimension.width << '§' << t_dimension.height;
    t_requestName+= ss.str();
    int ressPos = checkForName(t_requestName, type,t_dimension, nameNeedForLoad);
    return (ressImgPartTexture[ressPos]);
}
sf::Texture* GlobalSys::requestTexture(std::string t_requestName)
{
    ressType type = img;
    int ressPos = checkForName(t_requestName, type);
    return (ressImgTexture[ressPos]);
}
sf::Music* GlobalSys::requestMusic(std::string t_requestName)
{
    ressType type = music;
    int ressPos = checkForName(t_requestName, type);
    return (ressMusic[ressPos]);
}
sf::SoundBuffer* GlobalSys::requestSound(std::string t_requestName)
{
    ressType type = sound;
    int ressPos = checkForName(t_requestName, type);
    return (ressSoundBuffer[ressPos]);
}

sf::Font* GlobalSys::requestFont(std::string t_requestName)
{
    ressType type = font;
    int ressPos = checkForName(t_requestName, type);
    return (ressFont[ressPos]);
}
int GlobalSys::checkForName(std::string t_check, ressType t_type, sf::IntRect t_dimension, std::string nameNeedForLoad)
{
switch(t_type)
    {
    case imgPart:
        for (unsigned int i = 0 ; i < ressImgPartName.size(); i++)
        {
            if (t_check == *ressImgPartName[i])
                return (i);
        }
        createImgPartEntry(nameNeedForLoad, t_dimension, t_check);
        return (ressImgPartName.size()-1);
        break;
    }
    return 0;
}
int GlobalSys::checkForName(std::string t_check, ressType t_type)
{

    switch(t_type)
    {
    case img:
        for (unsigned int i = 0 ; i < ressImgName.size(); i++)
        {
            if (t_check == *ressImgName[i])
                return (i);
        }
        createImgEntry(t_check);
        return (ressImgName.size()-1);
        break;
    case sound:
        for (unsigned int i = 0 ; i < ressSoundBufferName.size(); i++)
        {
            if (t_check == *ressSoundBufferName[i])
                return (i);
        }
        createSoundEntry(t_check);
        return (ressSoundBufferName.size()-1);
        break;
    case music:
        for (unsigned int i = 0 ; i < ressMusicName.size(); i++)
        {
            if (t_check == *ressMusicName[i])
                return (i);
        }
        createMusicEntry(t_check);
        return (ressMusicName.size()-1);
        break;
    case font:
        for (unsigned int i = 0 ; i < ressFontName.size(); i++)
        {
            if (t_check == *ressFontName[i])
                return (i);
        }
        createFontEntry(t_check);
        return (ressFontName.size()-1);
        break;
    }
    return 0;
}

void GlobalSys::createImgEntry(std::string t_create)
{
    ressImgTexture.push_back(new sf::Texture);
    ressImgName.push_back(new std::string);
    *ressImgName[ressImgName.size()-1] = t_create;
    if(!ressImgTexture[ressImgTexture.size()-1]->loadFromFile(t_create))
    {
        std::cout << "WARNING WARNING WARNING ... le fichier suivant n'a pas pu être charger: " << t_create << " verifiez que le fichier existe, si c'est pas le cas t'es vraiment une merde ... \n";
    }
    std::cout << "ENTRY CREATED (img) \n";
}
void GlobalSys::createImgPartEntry(std::string t_create, sf::IntRect t_dimension, std::string t_name)
{
    ressImgPartTexture.push_back(new sf::Texture);
    ressImgPartName.push_back(new std::string);
    *ressImgPartName[ressImgPartName.size()-1] = t_name;
    if(!ressImgPartTexture[ressImgPartTexture.size()-1]->loadFromFile(t_create, t_dimension))
    {
        std::cout << "WARNING WARNING WARNING ... le fichier suivant n'a pas pu être charger: " << t_create << " verifiez que le fichier existe, si c'est pas le cas t'es vraiment une merde ... \n";
    }
    std::cout << "ENTRY CREATED (imgPart) \n";
}
void GlobalSys::createMusicEntry(std::string t_create)
{
    ressMusic.push_back(new sf::Music);
    ressMusicName.push_back(new std::string);
    *ressMusicName[ressMusicName.size()-1] = t_create;
    if(!ressMusic[ressMusic.size()-1]->openFromFile(t_create))
    {
        std::cout << "WARNING WARNING WARNING ... le fichier suivant n'a pas pu être charger: " << t_create << " verifiez que le fichier existe, si c'est pas le cas t'es vraiment une merde ... \n";
    }
    std::cout << "ENTRY CREATED (music) \n";
}
void GlobalSys::createSoundEntry(std::string t_create)
{
    ressSoundBuffer.push_back(new sf::SoundBuffer);
    ressSoundBufferName.push_back(new std::string);
    *ressSoundBufferName[ressSoundBufferName.size()-1] = t_create;
    if(!ressSoundBuffer[ressSoundBuffer.size()-1]->loadFromFile(t_create))
    {
        std::cout << "WARNING WARNING WARNING ... le fichier suivant n'a pas pu être charger: " << t_create << " verifiez que le fichier existe, si c'est pas le cas t'es vraiment une merde ... \n";
    }
    std::cout << "ENTRY CREATED (sound) \n";
}
void GlobalSys::createFontEntry(std::string t_create)
{
    ressFont.push_back(new sf::Font);
    ressFontName.push_back(new std::string);
    *ressFontName[ressFontName.size()-1] = t_create;
    if(!ressFont[ressFont.size()-1]->loadFromFile(t_create))
    {
        std::cout << "WARNING WARNING WARNING ... le fichier suivant n'a pas pu être charger: " << t_create << " verifiez que le fichier existe, si c'est pas le cas t'es vraiment une merde ... \n";
    }
    std::cout << "ENTRY CREATED (font) \n";
}

    int GlobalSys::addEntity(entType type)
    {
        return (m_level->addEntity(type));
    }
    void GlobalSys::removeEntity(int id)
    {
        m_level->removeEntity(id);
    }
    Entity* GlobalSys::getEntityById(int id)
    {
        return (m_level->getEntityById(id));
    }

void GlobalSys::preload() //vous avez juste a faire une request normal sans recuperer la valeur de return
{

}
