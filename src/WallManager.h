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
    inline void clearWalls() { walls.clear(); };

    int getSizeWalls();
    bool wallsHere(sf::Vector2f cursor);

    sf::Vector2f wallPosition(size_t i);

    virtual void notifyExplosion(void *from, sf::Vector2f pos, bool faction);

    void drawWalls(sf::RenderWindow & window);

    std::vector<Wall> walls;

private:
    sf::Texture texture;
};


#endif //RAMPART_WALLMANAGER_H
