#ifndef ABSTRACTENTITY_H
#define ABSTRACTENTITY_H

#include <SFML/Graphics/Sprite.hpp>

class AbstractEntity
{
	public:
		AbstractEntity(const sf::Texture &texture);
		virtual ~AbstractEntity()=0;
	
		inline sf::Sprite getSprite() { return sprite; };
	
	protected:
		sf::Sprite sprite;
	
};

inline AbstractEntity::~AbstractEntity(){}

#endif