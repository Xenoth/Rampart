#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <cstdlib>
#include <iostream>
#include <sstream>

#include <ctime>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "TileMap.h"
#include "Wall.h"

class MapManager
{
	public:
		
		MapManager(){};

		bool generateMap(sf::Vector2u mapSize);

		inline bool isContructible(sf::Vector2u coord) { return (tiles.at(coord.y*mapSize.x+coord.x)==1); };
		inline bool isConstructibleCastle(sf::Vector2u coord) { return (tiles.at(coord.y*mapSize.x+coord.x)==2); };
		inline bool isNavigable(sf::Vector2u coord) { return (tiles.at(coord.y*mapSize.x+coord.x)==0); };

		inline bool inTerritory(sf::Vector2u coord) { return (tiles.at(coord.y*mapSize.x+coord.x)==3); };

		void drawMap(sf::RenderWindow & window, size_t frameCount);
		void remplissage(std::vector<Wall> walls, sf::Vector2u position);

		//sf::Vector2u getCastlePosition();
		bool wallsHere(std::vector<Wall> walls, sf::Vector2f cursor);
	
	private:
		
	TileMap map1;
	TileMap map2;
	TileMap map3;
	std::vector<uint8_t> tiles;
	sf::Vector2u mapSize;
	
	
};

#endif