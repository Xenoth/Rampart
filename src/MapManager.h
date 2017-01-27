#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <ctime>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "TileMap.h"

class MapManager
{
	public:
		
		MapManager(){};

		bool generateMap(sf::Vector2u mapSize);

		inline bool isContructible(sf::Vector2u coord) { return (tiles.at(coord.y*mapSize.x+coord.x)==1); };
		inline bool isCastle(sf::Vector2u coord) { return (tiles.at(coord.y*mapSize.x+coord.x)==2); };
		inline bool isNavigable(sf::Vector2u coord) { return (tiles.at(coord.y*mapSize.x+coord.x)==0); };

		void drawMap(sf::RenderWindow & window, size_t frameCount);
	
	private:
		
	TileMap map1;
	TileMap map2;
	TileMap map3;
	std::vector<uint8_t> tiles;
	sf::Vector2u mapSize;
	
	
};

#endif