#include "BulletsManager.h"

BulletsManager::BulletsManager()
{
	texture.loadFromFile("../ressources/texture_bullet.png");

}

void BulletsManager::moveBullets()
{
	for(size_t i=0; i<bullets.size(); i++)
	{
		if(bullets.at(i).move())
		{
			bullets.erase(bullets.begin()+i);
		}
	}
}

void BulletsManager::drawBullets(sf::RenderWindow & window)
{
	for(size_t i=0; i<bullets.size(); i++)
		window.draw(bullets.at(i).getSprite());
}

void BulletsManager::notifyShoot(sf::Vector2f pos, sf::Vector2f target, bool faction, void *from)
{
    std::cout << "notifyShoot (BulletsManager.h) : from = " << from << std::endl;
	bullets.push_back(Bullet(texture, pos, target, faction, from));
	for (size_t  i = 0;  i < explosers.size(); i++) {
		bullets.at(bullets.size()-1).addExploser(explosers.at(i));
	}
}