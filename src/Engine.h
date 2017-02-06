#ifndef ENGINE_H
#define ENGINE_H


#include <cstdlib>
#include <iostream>
#include <sstream>


#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>

#include "GunsManager.h"
#include "BulletsManager.h"
#include "MapManager.h"
#include "ShipsManager.h"
#include "WallManager.h"
#include "Territory.h"
#include "CastlesManager.h"
#include "Audio.h"

class Engine
{
	public:
			
		Engine();
	
		void resetGame(sf::Vector2u mapSize);		
		void drawGame(sf::RenderWindow & window);

		bool addGun(sf::Vector2f cursor);
		void addShip(sf::Vector2f cursor);
		void addShips();

		void addWall(sf::Vector2f cursor);

		inline void pause() { audio.pause(); };
		inline void resume() { audio.resume(); };
		void update(sf::Vector2f mouse);
		
		bool chooseCastle(sf::Vector2f cursor);
		
		bool shootGun(sf::Vector2f target);

		int getSizeGuns();
		int getSizeShips();
		int getSizeWalls();

		void testTerritory();

		void moveOrShoot();
	
		void generateWall();

		void switchStepPartie(sf::Event event, sf::RenderWindow &window);
		void setStepPartie(int i);
		int getStepPartie();
		void introPartie(sf::RenderWindow &window, char *texte);
		void pause_game(sf::RenderWindow &window);
		void game_intro(sf::RenderWindow &window);

		void move();
		void printTimer(sf::Text chrono, sf::RenderWindow &window, sf::Event event);
		void newPartieQuestion(sf::RenderWindow &window);

		void addNbShips(int nbNewShips);

		sf::Clock clock;
		sf::Time pauseClock;
		bool pauseGame;

		sf::Font fontAncient;
		sf::Texture texture;
	
	private:

        sf::Vector2u cursor2Grid(sf::Vector2f cursor);

		std::vector<sf::Vector2<int> > generateCloud(size_t height_range, size_t width_range);

		GunsManager gunsManager;
		BulletsManager bulletsManager;
		ShipsManager shipsManager;
		MapManager mapManager;
		WallManager wallManager;
		Territory territory;
		CastlesManager castlesManager;

		Audio audio;

		size_t frameCount;

		int stepPartie;
		bool newStep;
};

#endif