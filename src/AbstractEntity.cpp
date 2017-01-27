#include "AbstractEntity.h"

AbstractEntity::AbstractEntity(const sf::Texture &texture)
{
	sprite.setTexture(texture, true);
	sprite.setOrigin(32/2, 32/2);
}