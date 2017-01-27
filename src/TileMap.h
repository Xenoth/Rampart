#ifndef TILEMAP_H
#define TILEMAP_H

#include <stdint.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>


class TileMap : public sf::Drawable, public sf::Transformable
{
	public:
		TileMap(){};
		
		bool load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<uint8_t> tiles, sf::Vector2u mapSize);
	
	private:

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		sf::VertexArray m_vertices;
		sf::Texture m_tileset;
};

#endif