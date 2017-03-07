#include "ShipsManager.h"
#include "GunsManager.h"

using namespace std;

ShipsManager::ShipsManager()
{
    texture.loadFromFile("../ressources/texture_ship.png");
}

void ShipsManager::placeShip(sf::Vector2f pos)
{
    ships.push_back(Ship(texture, pos));
    for (size_t i = 0; i < shooters.size(); i++)
    {
        //Add here Exploser
        ships.back().addShooter(shooters.at(i));
    }
}

bool ShipsManager::shipsHere(sf::Vector2f cursor){
    for (int i = 0; i < ships.size(); ++i)
    {
        if ( (int)(ships.at(i).getPos().x/32) == (int)(cursor.x/32) && (int)(ships.at(i).getPos().y/32) == (int)(cursor.y/32))
        {
            return true;
        }
    }
    return false;
}

void ShipsManager::drawShips(sf::RenderWindow & window)
{
    for(size_t i=0; i<ships.size(); i++)
    {
        window.draw(ships.at(i).getSprite());
    }
}

bool ShipsManager::AShipCanShoot(size_t i)
{
    return ships.at(i).canShoot;
}

void ShipsManager::ChangeCanShoot(size_t i)
{
    ships.at(i).canShoot = (!ships.at(i).canShoot);
}

void ShipsManager::setCanShoot(size_t i)
{
    ships.at(i).canShoot = true;
}

void ShipsManager::setCanShootAll()
{
    for(size_t i=0; i<ships.size(); i++)
    {
        setCanShoot(i);
    }
}

sf::Vector2f ShipsManager::getPositionShip(size_t i)
{
    return ships.at(i).getPos();
}

void ShipsManager::move(size_t i, sf::Vector2f pos){
    ships.at(i).move(pos);
}

void ShipsManager::shoot(size_t i, sf::Vector2f target)
{
    ships.at(i).shoot(ships.at(i).getPos(), target, false, &ships.at(i));
    ships.at(i).canShoot=false;
}

void ShipsManager::notifyExplosion(void *from, sf::Vector2f pos, bool faction)
{
    if(!faction)
    {
        //Gun *p_from = static_cast<Gun *>(from);
        //Reset shoot
        Ship *p_from = static_cast<Ship *>(from);
        for(size_t i = 0; i < ships.size(); i++)
        {
            if(&(ships.at(i))==p_from)
            {
                ships.at(i).canShoot=true;
                break;
            }
        }
    }
    else
        for(size_t i = 0; i < ships.size(); i++)
        {
            if(!(ships.at(i).getPos().x<=pos.x-31|| ships.at(i).getPos().y<=pos.y-31 || ships.at(i).getPos().x>=pos.x+31 || ships.at(i).getPos().y>=pos.y+31))
            {
                ships.erase(ships.begin()+i);
                return;
            }
        }
}


size_t ShipsManager::getSizeShips()
{
    return ships.size();
}

bool ShipsManager::AShipHasDestination(size_t i)
{
    return ships.at(i).hasDestination;
}

void ShipsManager::ShipSetDestination(size_t i, sf::Vector2f destination)
{
    ships.at(i).destination = destination;
    ships.at(i).hasDestination = true;
}

sf::Vector2f ShipsManager::getDestination(size_t i)
{
    return ships.at(i).getDestination();
}


void ShipsManager::setNoneDestination(size_t i)
{
    ships.at(i).hasDestination = false;
}