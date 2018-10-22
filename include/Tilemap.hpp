

#ifndef TILEMAP_HPP_INCLUDED
#define TILEMAP_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class TileMap : public sf::Drawable, public sf::Transformable
{
    public:
        bool load(const std::string& tileset, sf::Vector2u tileSize, std::vector<std::vector<int> > const& tiles, unsigned int width, unsigned int height);
        void reloadBlock(sf::Vector2i posBlock,int idBlock);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // on applique la transformation
            states.transform *= getTransform();

            // on applique la texture du tileset
            states.texture = &m_tileset;

            // et on dessine enfin le tableau de vertex
            target.draw(m_vertices, states);
        }

        sf::VertexArray m_vertices;
        sf::Texture m_tileset;
        int m_width;
        int m_height;
        sf::Vector2u m_tileSize;
};


#endif // TILEMAP_HPP_INCLUDED
