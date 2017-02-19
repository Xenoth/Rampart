#include <cmath>
#include "GunsManager.h"

GunsManager::GunsManager()
{
	texture.loadFromFile("ressources/texture_gun.png");
}

void GunsManager::placeGun(sf::Vector2f pos)
{
	guns.push_back(Gun(texture, pos));
	for(size_t i=0; i < shooters.size(); i++)
	{
		guns.back().addShooter(shooters.at(i));
	}
}

bool GunsManager::gunsHere(sf::Vector2f cursor)
{
	for (int i = 0; i < guns.size(); ++i)
    {
        if ( (int)(guns.at(i).getPos().x/32) == (int)(cursor.x/32) && (int)(guns.at(i).getPos().y/32) == (int)(cursor.y/32))
        {
            return true;
        }
    }
    return false;
}

void GunsManager::drawGuns(sf::RenderWindow & window)
{
	for(size_t i=0; i<guns.size(); i++)
	{
		window.draw(guns.at(i).getSprite());
	}
}

bool GunsManager::shoot(sf::Vector2f target)
{
	for(size_t i=0; i<guns.size(); i++)
	{
		if(guns.at(i).canShoot)
		{
			guns.at(i).shoot(guns.at(i).getPos(), target, true, &guns.at(i));
			guns.at(i).canShoot=false;
			return true;
		}
	}
	return false;
}

void GunsManager::rotateGuns(sf::Vector2f mouse)
{
	for(size_t i = 0; i < guns.size(); i++) {
		guns.at(i).setRotation(-atan2(mouse.x - guns.at(i).getPos().x, mouse.y - guns.at(i).getPos().y) * 180 / 3.14159);
	}
}


void GunsManager::notifyExplosion(void *from, sf::Vector2f pos, bool faction)
{
	if(faction)
	{
		Gun *p_from = static_cast<Gun *>(from);
		for(size_t i = 0; i < guns.size(); i++)
		{
			if(&(guns.at(i))==p_from)
			{
				guns.at(i).canShoot=true;
				break;
			}
		}
	}
	else
		for(size_t i = 0; i < guns.size(); i++)
		{
			if(!(guns.at(i).getPos().x<=pos.x-31|| guns.at(i).getPos().y<=pos.y-31 || guns.at(i).getPos().x>=pos.x+31 || guns.at(i).getPos().y>=pos.y+31))
            {
				guns.erase(guns.begin()+i);
				return;
			}
		}
}


size_t GunsManager::getSizeGuns()
{
	return guns.size();
}

sf::Vector2f GunsManager::gunPosition(size_t i)
{
	return guns.at(i).getPos();
}