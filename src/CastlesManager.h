//
// Created by xenoth on 04/02/17.
//

#ifndef RAMPART_CASTLESMANAGER_H
#define RAMPART_CASTLESMANAGER_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Castle.h"

class CastlesManager {

public:
    CastlesManager();

    void drawCastles(sf::RenderWindow &window);
    inline void clearCastles() { castles.clear(); };

    std::vector<Castle> castles;

private:
    sf::Texture texture;

};


#endif //RAMPART_CASTLESMANAGER_H
