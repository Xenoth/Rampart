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
			{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
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

/*
sf::Vector2u MapManager::getCastlePosition(){
	for (size_t i = 0; i < mapSize.x; ++i)
	{
		for (int j = 0; j < mapSize.y; ++j)
		{
			if (tiles.at(j*mapSize.x+i)==2)
			{
				return sf::Vector2u((uint)i, (uint)j);
			}
		}
	}
	return sf::Vector2u((uint)0, (uint)0);
}
*/


void MapManager::remplissage(std::vector<Wall> walls, sf::Vector2u position){
	std::cout << "REMPLISSAGE"  << std::endl;
	if (isConstructibleCastle(position))
	{
		std::cout << "\tCastle"  << std::endl;
		remplissage(walls, sf::Vector2u((uint)position.x+1, (uint)position.y));
        remplissage(walls, sf::Vector2u((uint)position.x-1, (uint)position.y));
        remplissage(walls, sf::Vector2u((uint)position.x, (uint)position.y+1));
        remplissage(walls, sf::Vector2u((uint)position.x, (uint)position.y-1));
	}
    if (tiles.at(position.y*mapSize.x+position.x) == 1)
    {
    	std::cout << "\tHerbe"  << std::endl;
        if (!wallsHere(walls, sf::Vector2f(position.x*32+16, position.y*32+16)))
        {
        	std::cout << "\tPas de Mur"  << std::endl;
        	//Changer la texture en territoire
        	tiles.at(position.y*mapSize.x+position.x)=3;
        	remplissage(walls, sf::Vector2u((uint)position.x+1, (uint)position.y));
        	remplissage(walls, sf::Vector2u((uint)position.x-1, (uint)position.y));
        	remplissage(walls, sf::Vector2u((uint)position.x, (uint)position.y+1));
        	remplissage(walls, sf::Vector2u((uint)position.x, (uint)position.y-1));
        }
    }
}


bool MapManager::wallsHere(std::vector<Wall> walls, sf::Vector2f cursor){
	for (int i = 0; i < walls.size(); ++i)
    {
        if ( (int)(walls.at(i).getPos().x/32) == (int)(cursor.x/32) && (int)(walls.at(i).getPos().y/32) == (int)(cursor.y/32))
        {
            return true;
        }
    }
    return false;
}