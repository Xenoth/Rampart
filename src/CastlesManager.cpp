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