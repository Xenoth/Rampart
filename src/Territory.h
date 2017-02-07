//
// Created by xenoth on 18/01/17.
//

#ifndef RAMPART_TERRITORY_H
#define RAMPART_TERRITORY_H

#include <cstdlib>
#include <iostream>
#include <sstream>

#include <stdint.h>
#include <vector>
#include "Wall.h"
#include "TileMap.h"
#include "Castle.h"

class Territory {

public :
    Territory();

    void loadTileMap(std::vector<uint8_t> tiles, sf::Vector2u mapSize);

    void calculateTerritory(std::vector<Wall> walls, sf::Vector2u castlePosition, bool isCastle);
    inline bool inTerritory(sf::Vector2u pos) { return (territory_map.at(pos.y*sizeMap.x+pos.x) == 2);};

    inline void drawTerritory(sf::RenderWindow & window) { window.draw(tileMap); };
    bool wallsHere(std::vector<Wall> walls, sf::Vector2f cursor);

    void whereIsTerritory();
    bool verificationTerritory(std::vector<Wall> walls);

private:

    TileMap tileMap;
    sf::Vector2u sizeMap;

    //0 = water, 1 = empty, 2 = Walls
    std::vector<uint8_t> territory_map;

};


#endif //RAMPART_TERRITORY_H
