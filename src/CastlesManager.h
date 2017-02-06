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

    void placeCastle(sf::Vector2f pos);
    size_t getSizeCastles();
    sf::Vector2f getPositionCastle(size_t i);
    bool castlesHere(sf::Vector2f cursor);

    std::vector<Castle> castles;

private:
    sf::Texture texture;

};


#endif //RAMPART_CASTLESMANAGER_H
