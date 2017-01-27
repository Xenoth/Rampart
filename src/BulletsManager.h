#ifndef BULLETSMANAGER_H
#define BULLETSMANAGER_H

#include "Bullet.h"
#include "Shooter.h"
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class BulletsManager : public Shooter
{
	public :
		
		BulletsManager();

		inline void addExploser2Bullets(Exploser *exploser) { explosers.push_back(exploser); };
		inline void clearBullets() { bullets.clear(); };

		void moveBullets();
		void drawBullets(sf::RenderWindow &window);

		void notifyShoot(sf::Vector2f pos, sf::Vector2f target, bool faction, void *from);
		
	private :

		std::vector<Exploser *> explosers;
		std::vector<Bullet> bullets;
		sf::Texture texture;	
};

#endif