#ifndef GUNSMANAGER_H
#define GUNSMANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include "Gun.h"
#include "Exploser.h"

class GunsManager : public Exploser
{

	public :
		
		GunsManager();

		inline void addShooter2Guns(Shooter *shooter) { shooters.push_back(shooter); };

		void placeGun(sf::Vector2f pos);
		inline void clearGuns() { guns.clear(); };

		void drawGuns(sf::RenderWindow & window);
		bool shoot(sf::Vector2f target);

		void rotateGuns(sf::Vector2f mouse);

		void notifyExplosion(void *from, sf::Vector2f pos, bool faction);
	
		size_t getSizeGuns();

		bool gunsHere(sf::Vector2f cursor);
		sf::Vector2f gunPosition(size_t i);

	private :

		std::vector<Shooter *> shooters;
		std::vector<Gun> guns;
		sf::Texture texture;
	
};

#endif