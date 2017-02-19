#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <sstream>

 
#include "config.h"
#include "Engine.h"

using namespace std;


int main(int argc, char* argv[])
{
	cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << endl;

	sf::RenderWindow window(sf::VideoMode(768, 768), "Rampart");
	window.setFramerateLimit(60);

	Engine engine;
	engine.game_intro(window);

    sf::Event event;

    sf::Text chrono;
	
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
            engine.switchStepPartie(event, window);
            switch(event.type){
                case sf::Event::Closed:
                {
                    window.close();
                }
                break;

                case sf::Event::KeyPressed:
                {
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                    else if (event.key.code == sf::Keyboard::Space)
                    {

                        engine.setStepPartie(2);
                        engine.switchStepPartie(event, window);
                    }
                    else if (event.key.code == sf::Keyboard::P)
                    {
                        engine.pauseGame=true;
                    }
                }
                break;

                default:
                break;
            }
        }

        if(engine.pauseGame && window.isOpen())
        {
            engine.pauseClock = engine.clock.getElapsedTime() + engine.pauseClock;
            engine.pause();
            engine.pause_game(window);
            engine.pauseGame=false;
            engine.resume();
            engine.clock.restart();
        }

        engine.update(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y ));

		window.clear(sf::Color(255,255,255,255));
		engine.drawGame(window);

        engine.move();
        engine.printTimer(chrono, window, event);

        window.display();
    }
    return 0;
}