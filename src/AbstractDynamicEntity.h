#ifndef ABSTRACTDYNAMICENTITY_H
#define ABSTRACTDYNAMICENTITY_H

#include <SFML/System/Vector2.hpp>

#include "AbstractEntity.h"


class AbstractDynamicEntity : public AbstractEntity
{
	public:
		AbstractDynamicEntity(const sf::Texture &texture, sf::Vector2f pos);
		virtual ~AbstractDynamicEntity()=0;

		bool move();
	
		inline sf::Vector2f getPos() { return sprite.getPosition(); };
		sf::Vector2f getNextPos();
	
	protected:
		
		sf::Vector2f direction;
		
};

inline AbstractDynamicEntity::~AbstractDynamicEntity(){}
	
#endif