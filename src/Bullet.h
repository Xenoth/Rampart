#ifndef BULLET_H
#define BULLET_H

#include "AbstractDynamicEntity.h"
#include "Explosable.h"
#include "Shootable.h"
#include <cmath>

class Bullet : public AbstractDynamicEntity, public Explosable
{
	public:
		Bullet(const sf::Texture &texture, sf::Vector2f pos, sf::Vector2f target, bool faction, void *from);
		~Bullet();

		bool move();
		
	private:
		
		sf::Vector2f target;
		sf::Vector2f origin;
		bool faction;
		void *from;
};
	
#endif