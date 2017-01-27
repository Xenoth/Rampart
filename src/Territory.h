//
// Created by xenoth on 18/01/17.
//

#ifndef RAMPART_TERRITORY_H
#define RAMPART_TERRITORY_H


#include "Exploser.h"

class Territory : Exploser {

public :
    Territory();

    bool addWall(sf::Vector2f pos);
    bool eraseWall(sf::Vector2f pos);

    void initTerritory(sf::Vector2f pos);
    void calculateTerritory();
    bool inTerritory(sf::Vector2f pos);

    void clearWalls();

    void notifyExplosion(void *from, sf::Vector2f pos, bool faction);

private:

    sf::Vector2u sizeMap;

    //0 = nothing, 1 = Walls, 2 = Territory
    std::vector<__uint8_t> territory_map;

};


#endif //RAMPART_TERRITORY_H
