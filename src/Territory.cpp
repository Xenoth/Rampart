//
// Created by xenoth on 18/01/17.
//

#include "Territory.h"

Territory::Territory() {}

void Territory::loadTileMap(std::vector<uint8_t> tiles, sf::Vector2u mapSize){
    territory_map.clear();
    this->sizeMap = mapSize;
    for (size_t i = 0; i < tiles.size(); i++){
        if(tiles.at(i) != 0){
            territory_map.push_back(1);
        } else
            territory_map.push_back(0);
    }

    tileMap.load("ressources/tileset_territory.png", sf::Vector2u(32, 32), territory_map, sizeMap);

}


void Territory::calculateTerritory(std::vector<Wall> walls, sf::Vector2u castlePosition, bool isCastle){
    std::cout << "REMPLISSAGE"  << std::endl;
    if (isCastle)
    {
        std::cout << "\tCastle"  << std::endl;
        calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x+1, (uint)castlePosition.y), false);
        calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x-1, (uint)castlePosition.y), false);
        calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x, (uint)castlePosition.y+1), false);
        calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x, (uint)castlePosition.y-1), false);
    }
    if (territory_map.at(castlePosition.y*sizeMap.x+castlePosition.x) == 1)
    {
        std::cout << "\tHerbe"  << std::endl;
        if (!wallsHere(walls, sf::Vector2f(castlePosition.x*32+16, castlePosition.y*32+16)))
        {
            std::cout << "\tPas de Mur"  << std::endl;
            territory_map.at(castlePosition.y*sizeMap.x+castlePosition.x)=2;
            calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x+1, (uint)castlePosition.y), false);
            calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x-1, (uint)castlePosition.y), false);
            calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x, (uint)castlePosition.y+1), false);
            calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x, (uint)castlePosition.y-1), false);
        }
    }
    tileMap.load("ressources/tileset_territory.png", sf::Vector2u(32, 32), territory_map, sizeMap);
}


bool Territory::wallsHere(std::vector<Wall> walls, sf::Vector2f cursor){
    for (int i = 0; i < walls.size(); ++i)
    {
        if ( (int)(walls.at(i).getPos().x/32) == (int)(cursor.x/32) && (int)(walls.at(i).getPos().y/32) == (int)(cursor.y/32))
        {
            return true;
        }
    }
    return false;
}

void Territory::whereIsTerritory()
{
    for (int x = 0; x < sizeMap.x; ++x)
    {
        for (int y = 0; y < sizeMap.y; ++y)
        {
            if (territory_map.at(y*sizeMap.x+x) == 2)
            {
                //Territory
                std::cout << "Territory -> x,y : " << x << ", " << y << " -> " << territory_map.at(y*sizeMap.x+x) << std::endl;
            }
        }
    }
}