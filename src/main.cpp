#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <sstream>

 
#include "config.h"
#include "Engine.h"

using namespace std;

void game_intro(sf::RenderWindow &window){
	sf::Text titleGame;
    sf::Text powered;
	sf::Font fontAncient;
	sf::Texture textures[2];
	sf::Sprite logo_c;
	sf::Sprite logo_sfml;

	fontAncient.loadFromFile("ressources/ancient_medium.ttf");
	titleGame.setString("RAMPART");
	titleGame.setCharacterSize(120);
	titleGame.setFont(fontAncient);
	titleGame.setPosition(120,100);
    powered.setString("powered by");
    powered.setCharacterSize(40);
    powered.setFont(fontAncient);
    powered.setPosition(170, 440);

	textures[0].loadFromFile("ressources/logo_c.png");
	textures[1].loadFromFile("ressources/logo_sfml.png");
	logo_c.setTexture(textures[0]);
	logo_sfml.setTexture(textures[1]);
	logo_c.setPosition(200,500);
	logo_sfml.setPosition(330,510);

	window.clear(sf::Color(0,0,0,255));
	window.draw(titleGame);
	window.draw(logo_c);
	window.draw(logo_sfml);
    window.draw(powered);
	window.display();

	usleep(2500*1000);
	window.clear(sf::Color(0,0,0,255));

    sf::Text command_title, command_mouse_1, /*command_mouse_2,*/ command_mouse_3, command_pause, command_reset, command_exit, confirm;
    command_title.setString("Controlls");
    command_mouse_1.setString("Mouse left : place a gun");
    //command_mouse_2.setString("Mouse middle : place a ship");
    command_mouse_3.setString("Mouse right : fire");
    command_pause.setString("Keyboard P : pause/resume");
    command_reset.setString("Keyboard Space : reset");
    command_exit.setString("Keyboard Escape : exit");
    confirm.setString("Press Space to Start");
    command_title.setFont(fontAncient);
    command_mouse_1.setFont(fontAncient);
    //command_mouse_2.setFont(fontAncient);
    command_mouse_3.setFont(fontAncient);
    command_pause.setFont(fontAncient);
    command_reset.setFont(fontAncient);
    command_exit.setFont(fontAncient);
    confirm.setFont(fontAncient);
    command_title.setCharacterSize(40);
    command_mouse_1.setCharacterSize(25);
    //command_mouse_2.setCharacterSize(25);
    command_mouse_3.setCharacterSize(25);
    command_pause.setCharacterSize(25);
    command_reset.setCharacterSize(25);
    command_exit.setCharacterSize(25);
    confirm.setCharacterSize(30);
    command_title.setPosition(120,100);
    command_mouse_1.setPosition(140,150);
    //command_mouse_2.setPosition(140,200);
    command_mouse_3.setPosition(140,250);
    command_pause.setPosition(140,300);
    command_reset.setPosition(140,350);
    command_exit.setPosition(140,400);
    confirm.setPosition(120, 600);

    window.draw(command_title);
    window.draw(command_mouse_1);
    //window.draw(command_mouse_2);
    window.draw(command_mouse_3);
    window.draw(command_pause);
    window.draw(command_reset);
    window.draw(command_exit);
    window.draw(confirm);
    window.display();

    sf::Event event;

    while(1) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space)
                    return;
            }
        }
    }
}

void pause_game(sf::RenderWindow &window){
    sf::Texture texture;
    sf::Sprite background;
    texture.loadFromFile("ressources/black_opacity.png");
    background.setTexture(texture);
    background.setScale(24, 24);

    sf::Text pause;
    sf::Font fontAncient;
    fontAncient.loadFromFile("ressources/ancient_medium.ttf");
    pause.setString("Game Paused");
    pause.setCharacterSize(100);
    pause.setFont(fontAncient);
    pause.setPosition(150, 300);

    window.draw(background);
    window.draw(pause);
    window.display();

    sf::Event event;

    while(1) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::P)
                    return;
            }
        }
    }
}

void introPartie(sf::RenderWindow &window, char *texte){
    sf::Texture texture;
    sf::Sprite background;
    texture.loadFromFile("ressources/black_opacity.png");
    background.setTexture(texture);
    background.setScale(24, 24);

    sf::Text introPartie, enterPress;
    sf::Font fontAncient;
    fontAncient.loadFromFile("ressources/ancient_medium.ttf");
    introPartie.setString(texte);
    introPartie.setCharacterSize(40);
    introPartie.setFont(fontAncient);
    introPartie.setPosition(150, 300);

    enterPress.setString("Press enter to continu");
    enterPress.setCharacterSize(40);
    enterPress.setFont(fontAncient);
    enterPress.setPosition(150, 360);

    window.draw(background);
    window.draw(introPartie);
    window.draw(enterPress);
    window.display();

    sf::Event event;

    while(1) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Return)
                    return;
            }
        }
    }
}

int main(int argc, char* argv[])
{
	cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << endl;

	sf::RenderWindow window(sf::VideoMode(768, 768), "Rampart");
	window.setFramerateLimit(60);

	Engine engine;
	game_intro(window);

	sf::Event event;
	engine.resetGame(sf::Vector2u(768/32, 768/32));
	bool pause = false;

    sf::Clock clock;
    int stepPartie = 0;
    bool newStep = false;
    sf::Time pauseClock;

    //cout << "PAUSE CLOCK : " << pauseClock.asSeconds() << endl;

    sf::Font fontAncient;
    fontAncient.loadFromFile("ressources/ancient_medium.ttf");
    sf::Text chrono;

	
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
            /*
            TO DO
                Detruire la cible quand l'obus du bateau la touche
                Choisir un chateau
                Placer les murs
                Verifier territoire
                Verifier placement guns dans territoire
            
            */
            switch(stepPartie)
            {
                case 0://Generate Map with Castle
                {
                    srand(time(NULL));
                    cout << "generating new world with Castle" << endl;
                    stepPartie = 1;
                    newStep = true;
                }
                break;

                case 1://Choose a castle
                {
                    if (newStep)
                    {
                        introPartie(window, "Choose a castle");
                        cout << "Choose a castle" << endl;
                        newStep = false;
                        clock.restart();
                        pauseClock = clock.getElapsedTime();
                    }
                    switch(event.type){
                        case sf::Event::MouseButtonPressed:
                        {
                            if (event.mouseButton.button == sf::Mouse::Left) {
                                cout << "Left Mouse Button Pressed" << endl;
                                if (engine.chooseCastle(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                                {
                                    stepPartie = 2;
                                    newStep = true;
                                }
                            }
                        }
                        break;

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
                                engine.resetGame(sf::Vector2u(768/32, 768/32));
                                stepPartie = 0;
                                clock.restart();
                                pauseClock = clock.getElapsedTime();
                            }
                            else if (event.key.code == sf::Keyboard::P)
                            {
                                pause=true;
                            }
                        }
                        break;

                        default:
                        break;
                    }
                }
                break;

                case 2://Generate wall
                {
                    if (newStep)
                    {
                        introPartie(window, "Generate wall");
                        cout << "Generate wall" << endl;
                        newStep = false;
                        clock.restart();
                        pauseClock = clock.getElapsedTime();
                    }
                    stepPartie = 3;
                    newStep = true;
                }
                break;

                case 3://Place 3 guns Max in 15 seconds
                {
                    if (newStep)
                    {
                        introPartie(window, "Place 3 guns Max in 15 seconds");
                        cout << "Place 3 guns Max" << endl;
                        newStep = false;
                        clock.restart();
                        pauseClock = clock.getElapsedTime();
                    }
                    cout << clock.getElapsedTime().asSeconds() + pauseClock.asSeconds() << endl;
                    cout << " NB Canon : " << engine.getSizeGuns() << endl;
                    if ((clock.getElapsedTime().asSeconds() + pauseClock.asSeconds()) < 15 || engine.getSizeGuns() == 3)
                    {
                        switch(event.type){
                            case sf::Event::MouseButtonPressed:
                            {
                                if (event.mouseButton.button == sf::Mouse::Left) {
                                    cout << "Left Mouse Button Pressed" << endl;
                                    engine.addGun(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                                    if (engine.getSizeGuns() == 3)
                                    {
                                        stepPartie = 4;
                                        newStep = true;
                                    }
                                }
                            }
                            break;

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
                                    engine.resetGame(sf::Vector2u(768/32, 768/32));
                                    stepPartie = 0;
                                    newStep = true;
                                }
                                else if (event.key.code == sf::Keyboard::P)
                                {
                                    pause=true;
                                }
                            }
                            break;

                            default:
                            break;
                        }
                    }
                    else
                    {
                        stepPartie = 4;
                        newStep = true;
                    }
                }
                break;

                case 4://Generate 3 ships
                {
                    if (newStep)
                    {
                        introPartie(window, "Generate 3 ships");
                        cout << "Generate 3 ships" << endl;
                        newStep = false;
                        clock.restart();
                        pauseClock = clock.getElapsedTime();
                    }
                    engine.addShips();
                    stepPartie = 5;
                    newStep = true;
                }
                break;

                case 5://Ships shoot walls & Player shoot ships with guns during 15 seconds
                {
                    if (newStep)
                    {
                        introPartie(window, "Ships shoot walls & Player shoot ships with guns during 15 seconds");
                        cout << "Ships shoot walls & Player shoot ships with guns during 15 seconds" << endl;
                        newStep = false;
                        clock.restart();
                        pauseClock = clock.getElapsedTime();
                    }
                    cout << clock.getElapsedTime().asSeconds() + pauseClock.asSeconds() << endl;

                    if ((clock.getElapsedTime().asSeconds() + pauseClock.asSeconds()) < 15 && engine.getSizeShips() != 0)
                    {
                        switch(event.type){
                            case sf::Event::MouseButtonPressed:
                            {
                                if (event.mouseButton.button == sf::Mouse::Right) {
                                    engine.shootGun(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                                }
                            }
                            break;

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
                                    engine.resetGame(sf::Vector2u(768/32, 768/32));
                                    stepPartie = 0;
                                    newStep = true;
                                }
                                else if (event.key.code == sf::Keyboard::P)
                                {
                                    pause=true;
                                }
                            }
                            break;

                            default:
                            break;
                        }
                    }
                    else
                    {
                        if (engine.getSizeShips() != 0)
                        {
                            stepPartie = 6;
                            newStep = true;
                        }
                        else
                        {
                            stepPartie = 7;
                            newStep = true;
                        }
                        
                    }
                }
                break;

                case 6://Player repair walls if they are a ships during 25 seconds
                {
                    if (newStep)
                    {
                        introPartie(window, "Player repair walls if they are a ships during 25 seconds");
                        cout << "Player repair walls" << endl;
                        newStep = false;
                        clock.restart();
                        pauseClock = clock.getElapsedTime();
                    }
                    cout << clock.getElapsedTime().asSeconds() + pauseClock.asSeconds() << endl;
                    
                    if (engine.getSizeShips() != 0)
                    {
                        if((clock.getElapsedTime().asSeconds() + pauseClock.asSeconds()) < 25)
                        {        
                            switch(event.type){
                                case sf::Event::MouseButtonPressed:
                                {
                                    if (event.mouseButton.button == sf::Mouse::Left) {
                                        //TO DO Add wall
                                        cout << "(" << event.mouseButton.x << "," << event.mouseButton.y << ")" << endl;
                                    }
                                }
                                break;

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
                                        engine.resetGame(sf::Vector2u(768/32, 768/32));
                                        stepPartie = 0;
                                        newStep = true;
                                    }
                                    else if (event.key.code == sf::Keyboard::P)
                                    {
                                        pause=true;
                                    }
                                }
                                break;

                                default:
                                break;
                            }
                        }
                        else
                        {
                            stepPartie = 5;
                            newStep = true;
                        }
                    }
                    else
                    {
                        stepPartie = 7;
                        newStep = true;
                    }
                }
                break;

                case 7://End of the game
                {
                    if (newStep)
                    {
                        introPartie(window, "End of the game");
                        cout << "End of the game" << endl;
                        newStep = false;
                        clock.restart();
                        pauseClock = clock.getElapsedTime();
                    }
                    window.close();
                }
                break;

                default:
                    cout << "Out of step" << endl;
                break;
            }
        
            
        }
		if(pause)
        {
            pauseClock = clock.getElapsedTime() + pauseClock;
            cout << " PAUSE CLOCK : " << pauseClock.asSeconds() << endl;
            engine.pause();
            pause_game(window);
            pause=false;
            engine.resume();
            clock.restart();
        
        }

        engine.update(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y ));

		window.clear(sf::Color(255,255,255,255));
		engine.drawGame(window);

        if(stepPartie==5)
            engine.moveOrShoot();

        //Affichage Chrono
        if (stepPartie == 3 || stepPartie == 5 || stepPartie == 6)
        {
            std::stringstream texteChrono;
            texteChrono.precision(2);
            texteChrono << "Chrono : " << clock.getElapsedTime().asSeconds() + pauseClock.asSeconds() << endl; 
            chrono.setString(texteChrono.str());
            chrono.setFont(fontAncient);
            chrono.setCharacterSize(40);
            chrono.setPosition(0,0);
            window.draw(chrono);
        }
        window.display();
    
    }

    return 0;
	
}