#ifndef RAMPART_WALL_H
#define RAMPART_WALL_H


#include "AbstractDynamicEntity.h"
#include "Shootable.h"

class Wall : public AbstractDynamicEntity, public Shootable
{

public:
    Wall(const sf::Texture &texture, const sf::Vector2f &pos);

    bool move(sf::Vector2f pos);
};


#endif //RAMPART_WALL_H
