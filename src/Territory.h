//
// Created by xenoth on 18/01/17.
//

#ifndef RAMPART_TERRITORY_H
#define RAMPART_TERRITORY_H


#include <stdint.h>
#include <vector>
#include "Wall.h"
#include "TileMap.h"
#include "Castle.h"

class Territory {

public :
    Territory();

    void loadTileMap(std::vector<uint8_t> tiles, sf::Vector2u mapSize);
    void calculateTerritory(std::vector<Wall> walls, std::vector<Castle> castles);
    inline bool inTerritory(sf::Vector2f pos) { return (territory_map.at(pos.x*sizeMap.y+pos.y) == 2);};

    inline void drawTerritory(sf::RenderWindow & window) { window.draw(tileMap); };

private:

    TileMap tileMap;
    sf::Vector2u sizeMap;

    //0 = water, 1 = empty, 2 = Walls
    std::vector<uint8_t> territory_map;

};


#endif //RAMPART_TERRITORY_H
