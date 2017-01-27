#include "AbstractStaticEntity.h"

AbstractStaticEntity::AbstractStaticEntity(const sf::Texture &texture, sf::Vector2f pos)
:AbstractEntity::AbstractEntity(texture)
{
	sprite.setPosition(pos);
}