#ifndef GlobalSys_H_INCLUDED
#define GlobalSys_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include "allEnum.h"

class Entity;
class World;
class Level;

enum ressType {img, imgPart, sound, music, font};


class GlobalSys
{
public:
    GlobalSys();
    void giveWorld(World* t_world);
    sf::Texture* requestTexture(std::string t_requestName); //request a texture (le name doit etre du type nom.png ou .jpg)
    sf::Texture* requestTexture(std::string t_requestName, sf::IntRect t_dimension); //permet de ne recuperer qu'une partie du fichier en tant que texture, comme pour le tileMap
    sf::Music* requestMusic(std::string t_requestName);
    sf::SoundBuffer* requestSound(std::string t_requestName);
    sf::Font* requestFont(std::string t_requestName);



    void preload();//allez dans le .cpp pour definir ce que vous voulez preload lors du demarage, nottement pour les truc lourd comme les grandes images c'est utile

//   void releaseMemory(); //a apeller lors de la fermeture du programme, cela delete toutes les textures
protected:

//event sys et utilitaire

    Level* m_level;
    World* m_world;
public:
    World* getWorld();

    int addEntity(entType type); //la valeur de renvoi est en fait l'id de l'entity qui a été crer en vue de son initialisation, et de sa gestion
    void removeEntity(int id);
    Entity* getEntityById(int id);


    float calculateDistance(sf::Vector2f pt1, sf::Vector2f pt2);
    void fillCircle(sf::Vector2f t_pos, int rad, int type); //world edit commande, sinon, fait comme son nom l'indique, le deuxiem prametre est le type de block qui ecrasera les ancien, attention, en dessous d'un radius de 4 ca fait un carré
    void fillSquare(sf::Vector2f t_pos, int rad, int type); //meme chose que le precedant, mais en carré
    void setBlock(sf::Vector2f t_pos, int type); //remplace un block precis par un autre type precis, qui est defini par le deuxiem parametre
    int getBlock(sf::Vector2f t_pos); //return le type du block en question


























//GlobalSys
    int checkForName(std::string t_check, ressType t_type);
    int checkForName(std::string t_check, ressType t_type, sf::IntRect t_dimension, std::string nameNeedForLoad);
    void createImgEntry(std::string t_create);
    void createImgPartEntry(std::string t_create, sf::IntRect t_dimension, std::string t_name);
    void createMusicEntry(std::string t_create);
    void createSoundEntry(std::string t_create);
    void createFontEntry(std::string t_create);

    //graph
    std::vector<std::string*> ressImgName;
    std::vector<sf::Texture*> ressImgTexture;
    std::vector<std::string*> ressImgPartName;
    std::vector<sf::Texture*> ressImgPartTexture;
    //son
    std::vector<std::string*> ressSoundBufferName;
    std::vector<sf::SoundBuffer*> ressSoundBuffer;
    std::vector<std::string*> ressMusicName;
    std::vector<sf::Music*> ressMusic;
    //autre
    std::vector<std::string*> ressFontName;
    std::vector<sf::Font*> ressFont;

};

#endif // GlobalSys_H_INCLUDED
