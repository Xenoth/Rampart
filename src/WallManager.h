//
// Created by xenoth on 04/02/17.
//

#ifndef RAMPART_WALLMANAGER_H
#define RAMPART_WALLMANAGER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Exploser.h"
#include "Wall.h"

class WallManager : public Exploser {

public:
    WallManager();

    inline void addWall(sf::Vector2f pos) { walls.push_back(Wall(texture, pos)); };

    virtual void notifyExplosion(void *from, sf::Vector2f pos, bool faction);

    inline void clearWalls() { walls.clear(); };

    void drawWalls(sf::RenderWindow & window);

    int getSizeWalls();

    bool wallsHere(sf::Vector2f cursor);

    std::vector<Wall> walls;
    sf::Vector2f wallPosition(size_t i);

private:
    sf::Texture texture;
};


#endif //RAMPART_WALLMANAGER_H
