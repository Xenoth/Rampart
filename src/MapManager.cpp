#include "MapManager.h"

bool MapManager::generateMap(sf::Vector2u mapSize)
{
	this->mapSize=mapSize;
	tiles.clear();

	uint8_t tmp[24][24] = {
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
			{0,0,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
			{0,0,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,0,0,0,0,0,0},
			{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
			{0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
			{0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
			{0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0},
			{0,0,0,0,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};

	for(size_t i=0; i<mapSize.x; i++){
		for(size_t j=0; j<mapSize.y; j++)
		{
			tiles.push_back(tmp[i][j]);
		}
	}
	//Simple coast

	srand(time(NULL));
	size_t coast=mapSize.x/3+rand()%5;
	for(size_t i=0; i<mapSize.y; i++)
	{
		uint8_t range=rand()%3;
		for(size_t j=0; j<mapSize.x; j++)
		{
			if(j>coast+range)
				tiles.push_back(0);
			else if(j<=coast+range)
				tiles.push_back(1);
		}
	}
	
	
	if(!map1.load("ressources/tileset1.png", sf::Vector2u(32, 32), tiles, mapSize))
		return false;
	if(!map2.load("ressources/tileset2.png", sf::Vector2u(32, 32), tiles, mapSize))
		return false;
	if(!map3.load("ressources/tileset3.png", sf::Vector2u(32, 32), tiles, mapSize))
		return false;
	return true;
}

void MapManager::drawMap(sf::RenderWindow & window, size_t frameCount)
{
	if(frameCount%60<15)
		window.draw(map1);
	else if(frameCount%60>=15 && frameCount%60<30 || frameCount%60>=45)
		window.draw(map2);
	else if(frameCount%60>=30 && frameCount%60<45)
		window.draw(map3);
}