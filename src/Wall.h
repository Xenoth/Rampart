//
// Created by xenoth on 04/02/17.
//

#ifndef RAMPART_WALL_H
#define RAMPART_WALL_H


#include "AbstractDynamicEntity.h"

class Wall : public AbstractDynamicEntity {

public:
    Wall(const sf::Texture &texture, const sf::Vector2f &pos);

    bool move(sf::Vector2f pos);
};


#endif //RAMPART_WALL_H
