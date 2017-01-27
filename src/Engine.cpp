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
}

void Engine::resetGame(sf::Vector2u mapSize)
{
	mapManager.generateMap(mapSize);
	gunsManager.clearGuns();
	bulletsManager.clearBullets();
	shipsManager.clearShips();
    audio.playMusic();
	frameCount=0;
}

void Engine::drawGame(sf::RenderWindow & window)
{
	mapManager.drawMap(window, frameCount);
	//castlesManager.drawCastles(window);
	gunsManager.drawGuns(window);
	shipsManager.drawShips(window);
	bulletsManager.drawBullets(window);
}

bool Engine::addGun(sf::Vector2f cursor) {
	sf::Vector2u coord = cursor2Grid(cursor);
	if(mapManager.isContructible(coord))
	{
		if (!gunsManager.gunsHere(cursor))
		{
			gunsManager.placeGun(sf::Vector2f(coord.x*32+16, coord.y*32+16));
		}
	}
}

bool Engine::chooseCastle(sf::Vector2f cursor) {
	sf::Vector2u coord = cursor2Grid(cursor);
	return mapManager.isCastle(coord);
}

void Engine::addShip(sf::Vector2f cursor) {
	sf::Vector2u coord = cursor2Grid(cursor);
	if(mapManager.isNavigable(coord))
	{
		if (!shipsManager.shipsHere(cursor))
		{
			shipsManager.placeShip(sf::Vector2f(coord.x*32+16, coord.y*32+16));
		}
	}
}

void Engine::addShips() {
	while(shipsManager.getSizeShips() != 3){
		cout << "NB Ships : " << shipsManager.getSizeShips() << endl;
		addShip(sf::Vector2f(rand()%769, rand()%769));
	}
}

bool Engine::shootGun(sf::Vector2f target) { 
	if(!gunsManager.shoot(target))
		std::cout << "cannot shoot"  << std::endl;
}

void Engine::update(sf::Vector2f mouse){
	bulletsManager.moveBullets();
	gunsManager.rotateGuns(mouse);
	frameCount++;
}

sf::Vector2u Engine::cursor2Grid(sf::Vector2f cursor) {
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

int Engine::getSizeGuns(){
	return gunsManager.getSizeGuns();
}

int Engine::getSizeShips(){
	return shipsManager.getSizeShips();
}

void Engine::moveOrShoot()
{
	for (size_t i = 0; i < shipsManager.getSizeShips(); ++i) {
        cout << "|-----------------Ship n°" << i << endl;
        //Retardement shoot

        if (shipsManager.AShipCanShoot(i)) {
            cout << "SHOOT" << endl;
            size_t target = (rand() % gunsManager.getSizeGuns());
            cout << "Target : " << target << endl;
            cout << gunsManager.gunPosition(target).x << ", " << gunsManager.gunPosition(target).y << endl;
            shipsManager.shoot(i, gunsManager.gunPosition(target));
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
        		cout << "-------------------------------------------" << destination.x << ", " << destination.y << endl;
        		shipsManager.ShipSetDestination(i, destination);
        	}


        	cout << "MOVE" << endl;
        	cout << "Destination : (" << shipsManager.getDestination(i).x << ", " << shipsManager.getDestination(i).y << ")" << endl;
        	
            cout << "From : (" << shipPos.x << ", " << shipPos.y << ")" << endl;
			



            //Tester si terre
            //Faire Rotation
		/*if (!shipsManager.shipsHere(cursor))
		{
			shipsManager.placeShip(sf::Vector2f(coord.x*32+16, coord.y*32+16));
		}*/



			if(shipPos.x < shipsManager.getDestination(i).x){
				shipPos.x = shipPos.x + 1;
			}
			if(shipPos.x > shipsManager.getDestination(i).x){
				shipPos.x = shipPos.x - 1;
			}
			if(shipPos.y < shipsManager.getDestination(i).y){
				shipPos.y = shipPos.y + 1;
			}
			if(shipPos.y > shipsManager.getDestination(i).y){
				shipPos.y = shipPos.y - 1;
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
	    		cout << "-------------------------------------------" << destination.x << ", " << destination.y << endl;
	    		shipsManager.ShipSetDestination(i, destination);
			}
			else
                shipsManager.move(i, shipPos);

			cout << "To : (" << shipPos.x << ", " << shipPos.y << ")" << endl;
			

        }
    }
}