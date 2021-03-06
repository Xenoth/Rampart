#include "Engine.h"

using namespace std;

Engine::Engine()
{
    gunsManager.addShooter2Guns(&bulletsManager);
    gunsManager.addShooter2Guns(&audio);

    shipsManager.addShooter2Ships(&bulletsManager);
    shipsManager.addShooter2Ships(&audio);

    bulletsManager.addExploser2Bullets(&gunsManager);
    bulletsManager.addExploser2Bullets(&shipsManager);
    bulletsManager.addExploser2Bullets(&audio);
    bulletsManager.addExploser2Bullets(&wallManager);

    stepPartie = 2;
    newStep = false;
    pauseGame = false;

    fontAncient.loadFromFile("../ressources/ancient_medium.ttf");
    texture.loadFromFile("../ressources/black_opacity.png");
    
}

void Engine::resetGame(sf::Vector2u mapSize)
{
    mapManager.generateMap(mapSize);
    gunsManager.clearGuns();
    bulletsManager.clearBullets();
    shipsManager.clearShips();
    wallManager.clearWalls();
    castlesManager.clearCastles();
    audio.playMusic();
    territory.loadTileMap(mapManager.getTiles(), mapManager.getMapSize());
    frameCount=0;
}

void Engine::drawGame(sf::RenderWindow & window)
{
    mapManager.drawMap(window, frameCount); 
    territory.drawTerritory(window);
    castlesManager.drawCastles(window);
    gunsManager.drawGuns(window);
    shipsManager.drawShips(window);
    wallManager.drawWalls(window);
    bulletsManager.drawBullets(window);
}

bool Engine::addGun(sf::Vector2f cursor) 
{
    sf::Vector2u coord = cursor2Grid(cursor);
    if(territory.inTerritory(coord))
    {
        if (!gunsManager.gunsHere(cursor) && !wallManager.wallsHere(cursor) && !castlesManager.castlesHere(cursor))
        {
            gunsManager.placeGun(sf::Vector2f(coord.x*32+16, coord.y*32+16));
            return true;
        }
    }
    return false;
}

bool Engine::chooseCastle(sf::Vector2f cursor) 
{
    sf::Vector2u coord = cursor2Grid(cursor);
    bool canConstructCastle = mapManager.isConstructibleCastle(coord);
    if (canConstructCastle)
    {
        castlesManager.placeCastle(sf::Vector2f(coord.x*32+16, coord.y*32+16));
    }
    return canConstructCastle;
}

void Engine::addWall(sf::Vector2f cursor)
{
    sf::Vector2u coord = cursor2Grid(cursor);
    if(mapManager.isContructible(coord))
    {
        if (!gunsManager.gunsHere(cursor) && !wallManager.wallsHere(cursor) && !castlesManager.castlesHere(cursor))
        {
            wallManager.addWall(sf::Vector2f(coord.x*32+16, coord.y*32+16));
        }
    }
}

void Engine::addShip(sf::Vector2f cursor) 
{
    sf::Vector2u coord = cursor2Grid(cursor);
    if(mapManager.isNavigable(coord))
    {
        if (!shipsManager.shipsHere(cursor))
        {
            shipsManager.placeShip(sf::Vector2f(coord.x*32+16, coord.y*32+16));
        }
    }
}

void Engine::addShips() 
{
    while(shipsManager.getSizeShips() != 3)
    {
        addShip(sf::Vector2f(rand()%769, rand()%769));
    }
}

void Engine::addNbShips(int nbNewShips)
{
    nbNewShips = nbNewShips + shipsManager.getSizeShips();
    while(shipsManager.getSizeShips() != nbNewShips)
    {
        addShip(sf::Vector2f(rand()%769, rand()%769));
    }
}

bool Engine::shootGun(sf::Vector2f target) 
{ 
    if(!gunsManager.shoot(target))
        std::cout << "cannot shoot"  << std::endl;
}

void Engine::update(sf::Vector2f mouse)
{
    bulletsManager.moveBullets();
    gunsManager.rotateGuns(mouse);
    frameCount++;
}

sf::Vector2u Engine::cursor2Grid(sf::Vector2f cursor) 
{
    return sf::Vector2u((uint)cursor.x/32, (uint)cursor.y/32);
}

vector<sf::Vector2<int> > Engine::generateCloud(size_t height_range, size_t width_range)
{
    vector<sf::Vector2<int> > cloud;
    for(size_t i=0; i<(height_range*width_range)/25; i++)
    {
        sf::Vector2<int> pos;
        bool isFree=true;
        
        do
        {
            isFree=true;
            pos.x=rand() % height_range;
            pos.y=rand() % width_range;
                
            for(size_t j=0; j<cloud.size(); j++)
            {
                if(pos.x >= cloud.at(j).x-3 && pos.x<=cloud.at(j).x+3 && pos.y >= cloud.at(j).y-3 && pos.y<=cloud.at(j).y+3)
                {
                    cout << "collision" << endl;
                    isFree=false;
                    break;
                }
            }
            
        }while(!isFree);
        
        cloud.push_back(pos);
    }   
    return cloud;
}

int Engine::getSizeGuns()
{
    return gunsManager.getSizeGuns();
}

int Engine::getSizeShips()
{
    return shipsManager.getSizeShips();
}

int Engine::getSizeWalls()
{
    return wallManager.getSizeWalls();
}

void Engine::moveOrShoot()
{
    for (size_t i = 0; i < shipsManager.getSizeShips(); ++i) {
        //Retardement shoot

        if (shipsManager.AShipCanShoot(i)) {
            sf::Vector2f cursor = sf::Vector2f(rand()%769, rand()%769);
            sf::Vector2u coord = cursor2Grid(cursor);
            
            while(!territory.inTerritory(coord) && !wallManager.wallsHere(cursor)){
                cursor = sf::Vector2f(rand()%769, rand()%769);
                coord = cursor2Grid(cursor);
            }
            
            shipsManager.shoot(i, cursor);
        } else {
            sf::Vector2f shipPos = shipsManager.getPositionShip(i);
            
            if (shipPos.x == shipsManager.getDestination(i).x && shipPos.y == shipsManager.getDestination(i).y)
            {
                shipsManager.setNoneDestination(i);
            }

            if (!shipsManager.AShipHasDestination(i))
            {
                sf::Vector2f destination;
                sf::Vector2u coord;
                destination = sf::Vector2f(rand()%769, rand()%769);
                    
                while(!mapManager.isNavigable(coord)){
                    destination = sf::Vector2f(rand()%769, rand()%769);
                    coord = cursor2Grid(destination);
                }
                
                shipsManager.ShipSetDestination(i, destination);
            }

            if(shipPos.x < shipsManager.getDestination(i).x){
                shipPos.x = shipPos.x + 0.5;
            }
            if(shipPos.x > shipsManager.getDestination(i).x){
                shipPos.x = shipPos.x - 0.5;
            }
            if(shipPos.y < shipsManager.getDestination(i).y){
                shipPos.y = shipPos.y + 0.5;
            }
            if(shipPos.y > shipsManager.getDestination(i).y){
                shipPos.y = shipPos.y - 0.5;
            }


            sf::Vector2u testNavigable = cursor2Grid(shipPos);
            if (!mapManager.isNavigable(testNavigable))
            {
                sf::Vector2f destination;
                sf::Vector2u coord;
                destination = sf::Vector2f(rand()%769, rand()%769);
                        
                while(!mapManager.isNavigable(coord))
                {
                    destination = sf::Vector2f(rand()%769, rand()%769);
                    coord = cursor2Grid(destination);
                }
                shipsManager.ShipSetDestination(i, destination);
            }
            else
                shipsManager.move(i, shipPos);

        }
    }
}

void Engine::generateWall()
{
    for (int i = 0; i < castlesManager.getSizeCastles(); ++i)
    {
        sf::Vector2u castlePosition = cursor2Grid(castlesManager.getPositionCastle(i));
        int xmin = castlePosition.x-2;
        int xmax = castlePosition.x+2;
        int ymin = castlePosition.y-2;
        int ymax = castlePosition.y+2; 

        for(int x = xmin; x <= xmax; x++)
        {
            addWall(sf::Vector2f(x*32+16, ymin*32+16));
            addWall(sf::Vector2f(x*32+16, ymax*32+16));    
        }
        for(int y = ymin+1; y <= ymax-1; y++)
        {
            addWall(sf::Vector2f(xmin*32+16, y*32+16));
            addWall(sf::Vector2f(xmax*32+16, y*32+16));    
        }
    }

    testTerritory();   
}

void Engine::testTerritory()
{
    territory.loadTileMap(mapManager.getTiles(), mapManager.getMapSize());
    for (int x = 0; x < 24; ++x)
    {
        for (int y = 0; y < 24; ++y)
        {
            if (mapManager.isConstructibleCastle(sf::Vector2u(x, y)))
            {
                sf::Vector2u castlePosition = sf::Vector2u(x, y);
                territory.makeBackUp();
                territory.calculateTerritory(wallManager.walls, castlePosition, true);
                
                if (!territory.verificationTerritory(wallManager.walls))
                {
                    territory.useBackUp();
                    territory.updateTileMap();
                    castlesManager.deleteCastle(sf::Vector2f(x*32+16, y*32+16));
                }else{
                    if(!castlesManager.castlesHere(sf::Vector2f(x*32+16, y*32+16)))
                    {
                        castlesManager.placeCastle(sf::Vector2f(x*32+16, y*32+16));
                    }
                }
            }
        }
    }
}

void Engine::checkGunsInTerritory()
{
    for(int gunNumber = 0 ; gunNumber < gunsManager.getSizeGuns() ; gunNumber++)
    {
        if(!(territory.inTerritory(cursor2Grid(gunsManager.gunPosition(gunNumber)))))
        {
            gunsManager.setGunCanShoot(false, gunNumber);
        }else{
            gunsManager.setGunCanShoot(true, gunNumber);
        }
    }
}

void Engine::setStepPartie(int i)
{
    stepPartie = i;
}

int Engine::getStepPartie()
{
    return stepPartie;
}

void Engine::switchStepPartie(sf::Event event, sf::RenderWindow &window)
{
    enum step {
                GAME_INTRO = 0, 
                GAME_PAUSE = 1,
                MAP_GENERATION = 2,
                CASTLE_CHOOSE = 3,
                WALL_GENERATION = 4,
                PLACE_3_GUNS = 5,
                SHIPS_GENERATION = 6,
                FIGHT = 7,
                REPARATION = 8,
                END = 9,
                PLACE_GUNS = 10
              };

    switch(stepPartie)
    {
        case GAME_INTRO:
        {
            cout << "GAME_INTRO" << endl;
            game_intro(window);
        }
        break;

        case GAME_PAUSE:
        {
            cout << "GAME_PAUSE" << endl;
        }
        break;

        case MAP_GENERATION:
        {
            cout << "MAP_GENERATION" << endl;
            srand(time(NULL));
            resetGame(sf::Vector2u(768/32, 768/32));
            stepPartie = 3;
            newStep = true;
        }
        break;

        case CASTLE_CHOOSE:
        {
            if (newStep)
            {
                introPartie(window, "Choose a castle");
                cout << "CASTLE_CHOOSE" << endl;
                newStep = false;
                clock.restart();
                pauseClock = clock.getElapsedTime();
            }
            switch(event.type)
            {
                case sf::Event::MouseButtonPressed:
                {
                    if (event.mouseButton.button == sf::Mouse::Left) 
                    {
                        if (chooseCastle(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        {
                            stepPartie = 4;
                            newStep = true;
                            switchStepPartie(event, window);
                        }
                    }
                }
                break;

                default:
                break;
            }
        }
        break;

        case WALL_GENERATION:
        {
            if (newStep)
            {
                introPartie(window, "Generate wall");
                cout << "WALL_GENERATION" << endl;
                newStep = false;
                clock.restart();
                pauseClock = clock.getElapsedTime();
            }
            generateWall();
            
            stepPartie = 5;
            newStep = true;
            
            territory.calculateNoTerritory(wallManager.walls);
            drawGame(window);
            
            if (!territory.verificationTerritory(wallManager.walls))
            {
                territory.loadTileMap(mapManager.getTiles(), mapManager.getMapSize());
                territory.drawTerritory(window);
                stepPartie = 9;
                newStep = true;
            }
        }
        break;

        case PLACE_3_GUNS:
        {
            if (newStep)
            {
                introPartie(window, "Place 3 guns in 15 seconds");
                cout << "PLACE_3_GUNS" << endl;
                newStep = false;
                clock.restart();
                pauseClock = clock.getElapsedTime();
            }
            
            if ((clock.getElapsedTime().asSeconds() + pauseClock.asSeconds()) < 15 || getSizeGuns() < 3)
            {
                switch(event.type){
                    case sf::Event::MouseButtonPressed:
                    {
                        if (event.mouseButton.button == sf::Mouse::Left) 
                        {
                            addGun(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                            if (getSizeGuns() == 3)
                            {
                                stepPartie = 6;
                                newStep = true;
                            }
                        }
                    }
                    break;

                    default:
                    break;
                }
            }
            else
            {
                stepPartie = 6;
                newStep = true;
            }
        }
        break;

        case SHIPS_GENERATION:
        {
            if (newStep)
            {
                introPartie(window, "Generate 3 ships");
                cout << "SHIPS_GENERATION" << endl;
                newStep = false;
                clock.restart();
                pauseClock = clock.getElapsedTime();
            }
            addShips();
            shipsManager.drawShips(window);
            stepPartie = 7;
            newStep = true;
        }
        break;

        case FIGHT:
        {
            if (newStep)
            {
                introPartie(window, "Fight Ships during 15 seconds");
                cout << "FIGHT" << endl;
                newStep = false;
                clock.restart();
                pauseClock = clock.getElapsedTime();
                checkGunsInTerritory();
            }
            
            if ((clock.getElapsedTime().asSeconds() + pauseClock.asSeconds()) < 15 && getSizeShips() != 0)
            {
                switch(event.type)
                {
                    case sf::Event::MouseButtonPressed:
                    {
                        if (event.mouseButton.button == sf::Mouse::Right) 
                        {
                            shootGun(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                        }
                    }
                    break;

                    default:
                    break;
                }
            }
            else
            {
                bulletsManager.clearBullets();
                shipsManager.setCanShootAll();
                if (getSizeShips() != 0)
                {
                    stepPartie = 8;
                    newStep = true;
                }
                else
                {
                    stepPartie = 9;
                    newStep = true;
                }
            }
        }
        break;

        case REPARATION:
        {
            if (newStep)
            {
                introPartie(window, "Place walls in 25 seconds");
                cout << "REPARATION" << endl;
                newStep = false;
                clock.restart();
                pauseClock = clock.getElapsedTime();
                testTerritory();
                territory.drawTerritory(window);
            }
            
            if (getSizeShips() != 0)
            {
                if((clock.getElapsedTime().asSeconds() + pauseClock.asSeconds()) < 25)
                {        
                    switch(event.type)
                    {
                        case sf::Event::MouseButtonPressed:
                        {
                            if (event.mouseButton.button == sf::Mouse::Left) 
                            {
                                addWall(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));    
                            }
                        }
                        break;

                        default:
                        break;
                    }
                }
                else
                {
                    addNbShips(2);
                    testTerritory();
                    territory.calculateNoTerritory(wallManager.walls);
                    drawGame(window);
                    
                    if (!territory.verificationTerritory(wallManager.walls))
                    {
                        territory.loadTileMap(mapManager.getTiles(), mapManager.getMapSize());
                        territory.drawTerritory(window);
                        stepPartie = 9;
                        newStep = true;
                        switchStepPartie(event, window);
                    }else
                    if (castlesManager.getSizeCastles() == 0)
                    {
                        stepPartie = 9;
                        newStep = true;
                        switchStepPartie(event, window);
                    }else{

                        territory.isARealTerritory(castlesManager.castles, wallManager.walls);
                        drawGame(window);

                        stepPartie = 10;
                        newStep = true;
                        switchStepPartie(event, window);
                    }
                }
            }
            else
            {
                stepPartie = 9;
                newStep = true;
            }
        }
        break;

        case END:
        {
            if(!window.isOpen()){
                exit(1);
            }
            if (newStep)
            {
                cout << "END" << endl;
                newStep = false;
                clock.restart();
                pauseClock = clock.getElapsedTime();
                newPartieQuestion(window);
            }else{
                window.close();
            }
        }
        break;

        case PLACE_GUNS:
        {
            if (newStep)
            {
                introPartie(window, "Place guns in 15 seconds");
                cout << "PLACE_GUNS" << endl;
                newStep = false;
                clock.restart();
                pauseClock = clock.getElapsedTime();
            }
            
            if (getSizeShips() != 0)
            {
                if((clock.getElapsedTime().asSeconds() + pauseClock.asSeconds()) < 15 && gunsManager.getSizeGuns() < castlesManager.getSizeCastles()*3)
                {        
                    switch(event.type)
                    {
                        case sf::Event::MouseButtonPressed:
                        {
                            if (event.mouseButton.button == sf::Mouse::Left) 
                            {
                                addGun(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                            }
                        }
                        break;

                        default:
                        break;
                    }
                }
                else
                {
                    stepPartie = 7;
                    newStep = true;
                    switchStepPartie(event, window);
                }
            }
            else
            {
                stepPartie = 9;
                newStep = true;
            }
        }
        break;

        default:
        {
            cout << "HOUSTON !! We have a problem !!!" << endl;
        }
        break;
    }
}


void Engine::introPartie(sf::RenderWindow &window, char *texte){
    sf::Sprite background;
    background.setTexture(texture);
    background.setScale(24, 24);

    sf::Text introPartie, enterPress;
    introPartie.setString(texte);
    introPartie.setCharacterSize(40);
    introPartie.setFont(fontAncient);
    introPartie.setPosition(150, 300);

    enterPress.setString("Press enter to continue");
    enterPress.setCharacterSize(40);
    enterPress.setFont(fontAncient);
    enterPress.setPosition(150, 360);

    window.draw(background);
    window.draw(introPartie);
    window.draw(enterPress);
    window.display();

    sf::Event event;

    while(1) 
    {
        while (window.pollEvent(event)) 
        {
            switch(event.type){
                case sf::Event::Closed:
                {
                    window.close();
                    return;
                }
                break;

                case sf::Event::KeyPressed:
                {
                    if (event.key.code == sf::Keyboard::Return)
                    {
                        window.clear(sf::Color(255,255,255,255));
                        drawGame(window);
                        return;
                    }
                    else if (event.key.code == sf::Keyboard::Escape) 
                    {
                        window.close();
                        return;
                    }
                    else if (event.key.code == sf::Keyboard::Space)
                    {

                        setStepPartie(2);
                        switchStepPartie(event, window);
                    }
                    else if (event.key.code == sf::Keyboard::P)
                    {
                        pauseGame=true;
                    }
                }
                break;

                default:
                break;
            }
        }
    }
}


void Engine::pause_game(sf::RenderWindow &window){
    sf::Sprite background;
    background.setTexture(texture);
    background.setScale(24, 24);

    sf::Text pause;
    pause.setString("Game Paused");
    pause.setCharacterSize(100);
    pause.setFont(fontAncient);
    pause.setPosition(150, 300);

    window.draw(background);
    window.draw(pause);
    window.display();

    sf::Event event;

    while(1) 
    {
        while (window.pollEvent(event)) 
        {
            switch(event.type){
                case sf::Event::Closed:
                {
                    window.close();
                    return;
                }
                break;

                case sf::Event::KeyPressed:
                {
                    if (event.key.code == sf::Keyboard::P)
                    {
                        window.clear(sf::Color(255,255,255,255));
                        drawGame(window);
                        return;
                    }
                    else if (event.key.code == sf::Keyboard::Escape) 
                    {
                        window.close();
                        return;
                    }
                    else if (event.key.code == sf::Keyboard::Space)
                    {
                        window.clear(sf::Color(255,255,255,255));
                        drawGame(window);
                        setStepPartie(2);
                        switchStepPartie(event, window);
                        return;
                    }
                }
                break;

                default:
                break;
            }
        }
    }
}



void Engine::game_intro(sf::RenderWindow &window)
{
    sf::Text titleGame;
    sf::Text powered;
    sf::Texture textures[2];
    sf::Sprite logo_c;
    sf::Sprite logo_sfml;

    titleGame.setString("RAMPART");
    titleGame.setCharacterSize(120);
    titleGame.setFont(fontAncient);
    titleGame.setPosition(120,100);
    powered.setString("powered by");
    powered.setCharacterSize(40);
    powered.setFont(fontAncient);
    powered.setPosition(170, 440);

    textures[0].loadFromFile("../ressources/logo_c.png");
    textures[1].loadFromFile("../ressources/logo_sfml.png");
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

    sf::sleep(sf::milliseconds(2500));
    
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

    while(1) 
    {
        while (window.pollEvent(event)) 
        {
            switch(event.type){
                case sf::Event::Closed:
                {
                    window.close();
                    return;
                }
                break;

                case sf::Event::KeyPressed:
                {
                    if (event.key.code == sf::Keyboard::Space)
                    {
                        return;
                    }
                    else if (event.key.code == sf::Keyboard::Escape) 
                    {
                        window.close();
                        return;
                    }
                }
                break;

                default:
                break;
            }
        }
    }
}

void Engine::move()
{
    if(stepPartie==7)
        moveOrShoot();
}

void Engine::printTimer(sf::Text chrono, sf::RenderWindow &window, sf::Event event)
{
    if (stepPartie == 5 || stepPartie == 7 || stepPartie == 8 || stepPartie == 10)
    {
        std::stringstream texteChrono;
        texteChrono.precision(2);
        texteChrono << "Chrono : " << clock.getElapsedTime().asSeconds() + pauseClock.asSeconds() << endl; 
        chrono.setString(texteChrono.str());
        chrono.setFont(fontAncient);
        chrono.setCharacterSize(40);
        chrono.setPosition(0,0);
        window.draw(chrono);
        
        if (stepPartie == 5 && (clock.getElapsedTime().asSeconds() + pauseClock.asSeconds()) >= 15)
        {
            stepPartie = 6;
            newStep = true;
            switchStepPartie(event, window);
        }
        if (stepPartie == 7 && ((clock.getElapsedTime().asSeconds() + pauseClock.asSeconds()) >= 15 || getSizeShips() == 0))
        {
            bulletsManager.clearBullets();
            shipsManager.setCanShootAll();
            if (getSizeShips() != 0)
            {
                stepPartie = 8;
                newStep = true;
            }
            else
            {
                stepPartie = 9;
                newStep = true;
            }
            switchStepPartie(event, window);
        }
        if (stepPartie == 8 && (clock.getElapsedTime().asSeconds() + pauseClock.asSeconds()) >= 25)
        {
            addNbShips(2);
            testTerritory();
            territory.calculateNoTerritory(wallManager.walls);
            drawGame(window);

            if (!territory.verificationTerritory(wallManager.walls))
            {
                territory.loadTileMap(mapManager.getTiles(), mapManager.getMapSize());
                territory.drawTerritory(window);
                stepPartie = 9;
                newStep = true;
                switchStepPartie(event, window);
            }
            else if (castlesManager.getSizeCastles() == 0)
            {
                stepPartie = 9;
                newStep = true;
                switchStepPartie(event, window);
            }else{

                territory.isARealTerritory(castlesManager.castles, wallManager.walls);
                
                drawGame(window);
                stepPartie = 10;
                newStep = true;
                switchStepPartie(event, window);
            }
        }
        if (stepPartie == 10 && (clock.getElapsedTime().asSeconds() + pauseClock.asSeconds()) >= 15)
        {
            stepPartie = 7;
            newStep = true;
            switchStepPartie(event, window);
        }
    }
}

void Engine::newPartieQuestion(sf::RenderWindow &window)
{
    sf::Sprite background;
    background.setTexture(texture);
    background.setScale(24, 24);

    sf::Text introPartie, enterPress;

    enterPress.setString("New Partie ? [O/N]");
    enterPress.setCharacterSize(40);
    enterPress.setFont(fontAncient);
    enterPress.setPosition(150, 360);

    window.draw(background);
    window.draw(enterPress);
    window.display();

    sf::Event event;

    while(1) 
    {
        while (window.pollEvent(event)) 
        {
            switch(event.type){

                case sf::Event::Closed:
                {
                    window.close();
                    return;
                }
                break;

                case sf::Event::KeyPressed:
                {
                    if (event.key.code == sf::Keyboard::Escape) 
                    {
                        window.close();
                        return;
                    }
                    else if (event.key.code == sf::Keyboard::O || event.key.code == sf::Keyboard::Space)
                    {
                         window.clear(sf::Color(255,255,255,255));
                        drawGame(window);
                        stepPartie = 2;
                        newStep = true;
                        switchStepPartie(event, window);
                        return;
                    }
                    else if (event.key.code == sf::Keyboard::N)
                    {
                        window.close();
                        return;
                    }
                }
                break;

                default:
                break;
            }
        }
    }
}