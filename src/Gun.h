#ifndef GUN_H
#define GUN_H

#include "AbstractStaticEntity.h"
#include "Shootable.h"

class Gun : public AbstractStaticEntity, public Shootable
{
	public:
		
		Gun(const sf::Texture &texture, sf::Vector2f pos);

		inline void setRotation(double angle) { sprite.setRotation(angle); };
	
		bool canShoot;

};

#endif