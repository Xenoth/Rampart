#include "Gun.h"

Gun::Gun(const sf::Texture &texture, sf::Vector2f pos)
:AbstractStaticEntity::AbstractStaticEntity(texture, pos)
{
		canShoot = true;
}
