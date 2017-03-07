#include "WallManager.h"

WallManager::WallManager() 
{
    texture.loadFromFile("../ressources/texture_wall.png");
}

void WallManager::notifyExplosion(void *from, sf::Vector2f pos, bool faction) 
{
    if(!faction)
        for(size_t i = 0; i < walls.size(); i++)
        {
            if(!(walls.at(i).getPos().x<=pos.x-31|| walls.at(i).getPos().y<=pos.y-31 || walls.at(i).getPos().x>=pos.x+31 || walls.at(i).getPos().y>=pos.y+31))
            {
                walls.erase(walls.begin()+i);
                return;
            }
        }
}


int WallManager::getSizeWalls()
{
	return walls.size();
}


void WallManager::drawWalls(sf::RenderWindow & window)
{
    for(size_t i=0; i<walls.size(); i++)
    {
        window.draw(walls.at(i).getSprite());
    }
}

bool WallManager::wallsHere(sf::Vector2f cursor)
{
	for (int i = 0; i < walls.size(); ++i)
    {
        if ( (int)(walls.at(i).getPos().x/32) == (int)(cursor.x/32) && (int)(walls.at(i).getPos().y/32) == (int)(cursor.y/32))
        {
            return true;
        }
    }
    return false;
}

sf::Vector2f WallManager::wallPosition(size_t i)
{
	return walls.at(i).getPos();
}