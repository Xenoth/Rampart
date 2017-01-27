#include "AbstractDynamicEntity.h"

AbstractDynamicEntity::AbstractDynamicEntity(const sf::Texture &texture, sf::Vector2f pos)
:AbstractEntity::AbstractEntity(texture)
{
	sprite.setPosition(pos);
}
	
sf::Vector2f AbstractDynamicEntity::getNextPos()
{
	return direction+getPos();
}