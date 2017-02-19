#include "Wall.h"

Wall::Wall(const sf::Texture &texture, const sf::Vector2f &pos)
        : AbstractDynamicEntity(texture, pos) {
}

bool Wall::move(sf::Vector2f pos) 
{
    this->sprite.setPosition(pos);
}