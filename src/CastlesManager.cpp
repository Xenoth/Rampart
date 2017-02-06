//
// Created by xenoth on 04/02/17.
//

#include "CastlesManager.h"

CastlesManager::CastlesManager() {
    texture.loadFromFile("ressources/texture_castle.png");
}

void CastlesManager::drawCastles(sf::RenderWindow & window)
{
    for(size_t i=0; i<castles.size(); i++)
        window.draw(castles.at(i).getSprite());
}

void CastlesManager::placeCastle(sf::Vector2f pos)
{
    castles.push_back(Castle(texture, pos));
}

size_t CastlesManager::getSizeCastles()
{
    return castles.size();
}

sf::Vector2f CastlesManager::getPositionCastle(size_t i)
{
    return castles.at(i).getPos();
}

bool CastlesManager::castlesHere(sf::Vector2f cursor){
	for (int i = 0; i < castles.size(); ++i)
    {
        if ( (int)(castles.at(i).getPos().x/32) == (int)(cursor.x/32) && (int)(castles.at(i).getPos().y/32) == (int)(cursor.y/32))
        {
            return true;
        }
    }
    return false;
}