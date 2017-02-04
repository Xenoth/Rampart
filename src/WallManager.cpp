//
// Created by xenoth on 04/02/17.
//

#include "WallManager.h"

WallManager::WallManager() {
    texture.loadFromFile("ressources/texture_wall.png");
}

void WallManager::notifyExplosion(void *from, sf::Vector2f pos, bool faction) {
    if(!faction)
        for(size_t i = 0; i < walls.size(); i++){
            if(!(walls.at(i).getPos().x<=pos.x-31|| walls.at(i).getPos().y<=pos.y-31 || walls.at(i).getPos().x>=pos.x+31 || walls.at(i).getPos().y>=pos.y+31))
            {
                walls.erase(walls.begin()+i);
                return;
            }
        }
}


