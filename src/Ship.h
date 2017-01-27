#ifndef SHIP_H
#define SHIP_H

#include <stdint.h>

#include <cstdlib>
#include <iostream>

#include "AbstractDynamicEntity.h"
#include "Shootable.h"


class Ship : public AbstractDynamicEntity, public Shootable
{
	public:
		
		Ship(const sf::Texture &texture, sf::Vector2f pos);

		bool canShoot;

		bool move(sf::Vector2f pos);

		bool hasDestination;

		sf::Vector2f destination;

		sf::Vector2f getDestination();		

	private:
		
		uint8_t life;
};
	
#endif