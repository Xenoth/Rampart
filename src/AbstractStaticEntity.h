#ifndef ABSTRACTSTATICENTITY_H
#define ABSTRACTSTATICENTITY_H

#include <SFML/System/Vector2.hpp>

#include "AbstractEntity.h"


class AbstractStaticEntity : public AbstractEntity
{
	public:
		AbstractStaticEntity(const sf::Texture &texture, sf::Vector2f pos);
		virtual ~AbstractStaticEntity()=0;
	
		sf::Vector2f getPos() { return sprite.getPosition(); };
};

inline AbstractStaticEntity::~AbstractStaticEntity(){}

#endif