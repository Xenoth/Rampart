#include <iostream>
#include "Shootable.h"

void Shootable::shoot(sf::Vector2f pos, sf::Vector2f target, bool faction, void *from) 
{
    for (size_t i = 0; i < shooters.size(); i++)
	{
        shooters.at(i)->notifyShoot(pos, target, faction, from);
	}
}

void Shootable::removeShooter(Shooter *shooter) 
{
    for(size_t i=0; i<shooters.size(); i++) 
    {
        if (shooters.at(i) == shooter) 
        {
            shooters.erase(shooters.begin() + i);
            break;
        }
    }
}