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
void Territory::calculateTerritory(std::vector<Wall> walls, std::vector<Castle> castles){
    //TODO

}