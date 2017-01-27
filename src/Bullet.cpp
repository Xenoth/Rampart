#include <iostream>
#include "Bullet.h"

Bullet::Bullet(const sf::Texture &texture, sf::Vector2f pos, sf::Vector2f target, bool faction, void *from)
:AbstractDynamicEntity::AbstractDynamicEntity(texture, pos)
{
	this->target=target;
	this->faction=faction;
	this->from=from;
	this->origin=pos;
	
	direction.x = target.x - pos.x;
	direction.y = target.y - pos.y;
	double norme = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
	direction.x = direction.x / norme*4;
	direction.y = direction.y / norme*4;
}

Bullet::~Bullet()
{}

bool Bullet::move()
{
	if(getNextPos().x<=target.x-3 || getNextPos().y<=target.y-3 || getNextPos().x>=target.x+3 || getNextPos().y>=target.y+3)
	{
		// parabola : f(x) = (x - x1) * (x - x2)
		//fx = scale
		// x = distanceOP(Origin 2 Position)
		// x1 = 0 (origin)
		// x2 = distanceOT (Origin 2 Target)
		double distanceOP = sqrt(pow(getPos().x - origin.x, 2) + pow(getPos().y - origin.y, 2));
		double distanceOT = sqrt(pow(target.x - origin.x, 2) + pow(target.y - origin.y, 2));
		double scale = abs((distanceOP - 0) * (distanceOP - distanceOT));


		scale*= 0.000080;
		if(scale<0.75)
			scale = 0.75;

		sprite.setScale(scale, scale);


		sprite.rotate(5);
		sprite.move(direction);
		return false;
	}
	explose(from, getNextPos(), faction);
	return true;
}