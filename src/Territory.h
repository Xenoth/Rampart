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

    void updateTileMap();

    void calculateTerritory(std::vector<Wall> walls, sf::Vector2u castlePosition, bool isCastle);
    void calculateNoTerritory(std::vector<Wall> walls);
    inline bool inTerritory(sf::Vector2u pos) { return (territory_map.at(pos.y*sizeMap.x+pos.x) == 2);};
    int countCaseEmpty();

    inline void drawTerritory(sf::RenderWindow & window) { window.draw(tileMap); };
    bool wallsHere(std::vector<Wall> walls, sf::Vector2f cursor);

    void whereIsTerritory();
    bool verificationTerritory(std::vector<Wall> walls);

    void makeBackUp();
    void useBackUp();

    void territorySideBySide(sf::Vector2u position);
    bool isARealTerritory(std::vector<Castle> castles, std::vector<Wall> walls);

private:

    TileMap tileMap;
    sf::Vector2u sizeMap;

    //0 = water, 1 = empty, 2 = Territory, 3 = can't be a Territory, 4 = Wall
    std::vector<uint8_t> territory_map;

    std::vector<uint8_t> backup_territory_map;

};


#endif //RAMPART_TERRITORY_H
