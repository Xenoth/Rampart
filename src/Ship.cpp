#include <cmath>
#include "Ship.h"

using namespace std;

Ship::Ship(const sf::Texture &texture, sf::Vector2f pos)
:AbstractDynamicEntity::AbstractDynamicEntity(texture, pos)
{
	life=2;
	canShoot = true;
	hasDestination = false;
}

bool Ship::move(sf::Vector2f pos)
{
    sf::Vector2f delta(pos.x - sprite.getPosition().x, pos.y - sprite.getPosition().y);
    sprite.setRotation(atan2(delta.y, delta.x) * 180 / (atan(1)*4) + 270);
    sprite.setPosition(pos);
}

sf::Vector2f Ship::getDestination()
{
	return destination;
}