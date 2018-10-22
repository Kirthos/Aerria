#include "../include/Tilemap.hpp"

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, std::vector<std::vector<int> > const& tiles, unsigned int width, unsigned int height)
{
    // on charge la texture du tileset
    if (!m_tileset.loadFromFile(tileset))
        return false;
    if(tiles[0][0] == -1)
        return false;
    m_width = width;
    m_height = height;
    m_tileSize = tileSize;
    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // on récupère le numéro de tuile courant
            int tileNumber = tiles[i][j];
            //std::cout<<tileNumber;

            // on en déduit sa position dans la texture du tileset
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];
            // on définit ses quatre coins
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // on définit ses quatre coordonnées de texture
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    return true;
}
    void TileMap::reloadBlock(sf::Vector2i posBlock,int idBlock)
    {
        int tileNumber = idBlock;
        int width = m_width;
        int i = posBlock.x;
        int j = posBlock.y;
         sf::Vector2u tileSize = m_tileSize;
        // on en déduit sa position dans la texture du tileset
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];
            // on définit ses quatre coins
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // on définit ses quatre coordonnées de texture
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
    }
