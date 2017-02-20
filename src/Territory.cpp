#include "Territory.h"

Territory::Territory() {}

void Territory::loadTileMap(std::vector<uint8_t> tiles, sf::Vector2u mapSize)
{
    territory_map.clear();
    this->sizeMap = mapSize;
    for (size_t i = 0; i < tiles.size(); i++)
    {
        if(tiles.at(i) != 0){
            territory_map.push_back(1);
            backup_territory_map.push_back(1);
        }else{
            territory_map.push_back(0);
            backup_territory_map.push_back(0);
        }
    }

    tileMap.load("ressources/tileset_territory.png", sf::Vector2u(32, 32), territory_map, sizeMap);
}

void Territory::updateTileMap()
{
    tileMap.load("ressources/tileset_territory.png", sf::Vector2u(32, 32), territory_map, sizeMap);
}

void Territory::calculateTerritory(std::vector<Wall> walls, sf::Vector2u castlePosition, bool isCastle)
{
    if (isCastle)
    {
        calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x+1, (uint)castlePosition.y), false);
        calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x-1, (uint)castlePosition.y), false);
        calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x, (uint)castlePosition.y+1), false);
        calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x, (uint)castlePosition.y-1), false);
    }
    if (territory_map.at(castlePosition.y*sizeMap.x+castlePosition.x) == 1)
    {
        if (!wallsHere(walls, sf::Vector2f(castlePosition.x*32+16, castlePosition.y*32+16)))
        {
            territory_map.at(castlePosition.y*sizeMap.x+castlePosition.x)=2;
            calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x+1, (uint)castlePosition.y), false);
            calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x-1, (uint)castlePosition.y), false);
            calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x, (uint)castlePosition.y+1), false);
            calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x, (uint)castlePosition.y-1), false);
        }
    }
    tileMap.load("ressources/tileset_territory.png", sf::Vector2u(32, 32), territory_map, sizeMap);
}

void Territory::territorySideBySide(sf::Vector2u position)
{
    if (backup_territory_map.at(position.y*sizeMap.x+position.x) == 2)
    {
        backup_territory_map.at(position.y*sizeMap.x+position.x)=9;
        territorySideBySide(sf::Vector2u((uint)position.x+1, (uint)position.y));
        territorySideBySide(sf::Vector2u((uint)position.x-1, (uint)position.y));
        territorySideBySide(sf::Vector2u((uint)position.x, (uint)position.y+1));
        territorySideBySide(sf::Vector2u((uint)position.x, (uint)position.y-1));
    }
}

bool Territory::isARealTerritory(std::vector<Castle> castles, std::vector<Wall> walls)
{
    makeBackUp();

    //Nb Walls
    for (int x = 0; x < sizeMap.x; ++x)
    {
        for (int y = 0; y < sizeMap.y; ++y)
        {
            if (wallsHere(walls, sf::Vector2f(x*32+16, y*32+16)) && backup_territory_map.at(y*sizeMap.x+x)==4)
            {
                backup_territory_map.at(y*sizeMap.x+x)=2;
            }
        }
    }

    for (int x = 0; x < sizeMap.x; ++x)
    {
        for (int y = 0; y < sizeMap.y; ++y)
        {
            if (wallsHere(walls, sf::Vector2f(x*32+16, y*32+16)) && backup_territory_map.at(y*sizeMap.x+x)==4)
            {
                backup_territory_map.at(y*sizeMap.x+x)=2;
            }
        }
    }
    
    for (int i = 0; i < castles.size(); ++i)
    {
        territorySideBySide(sf::Vector2u((uint)castles.at(i).getPos().x/32, (uint)castles.at(i).getPos().y/32));
    }

//Inversion
    for (int x = 0; x < sizeMap.x; ++x)
    {
        for (int y = 0; y < sizeMap.y; ++y)
        {
            if (backup_territory_map.at(y*sizeMap.x+x) == 2)
            {
                backup_territory_map.at(y*sizeMap.x+x) = 9;
            }
            else if (backup_territory_map.at(y*sizeMap.x+x) == 9)
            {
                backup_territory_map.at(y*sizeMap.x+x) = 2;
            } 
        }
    }

    useBackUp();
    tileMap.load("ressources/tileset_territory.png", sf::Vector2u(32, 32), backup_territory_map, sizeMap);

    //9? => if > 1 => game over
    for (int x = 0; x < sizeMap.x; ++x)
    {
        for (int y = 0; y < sizeMap.y; ++y)
        {
            if (backup_territory_map.at(y*sizeMap.x+x) == 9)
            {
                makeBackUp();
                return false;
            }  
        }
    }

    makeBackUp();
    return true;
}

void Territory::calculateNoTerritory(std::vector<Wall> walls)
{
    //SET WALLS
    for (int x = 0; x < sizeMap.x; ++x)
    {
        for (int y = 0; y < sizeMap.y; ++y)
        {
            if (wallsHere(walls, sf::Vector2f(x*32+16, y*32+16)))
            {
                territory_map.at(y*sizeMap.x+x) = 4;
            }  
        }
    }


    //CALCULATE NO TERRITORY
    int countUpdate = 1;
    while(countCaseEmpty()!=0 && countUpdate!=0)
    {
        countUpdate = 0;
        for (int x = 0; x < sizeMap.x; ++x)
        {
            for (int y = 0; y < sizeMap.y; ++y)
            {
                if (!wallsHere(walls, sf::Vector2f(x*32+16, y*32+16)) && territory_map.at(y*sizeMap.x+x) == 1)
                {
                    if (territory_map.at((y-1)*sizeMap.x+x) == 0 
                    || territory_map.at((y+1)*sizeMap.x+x) == 0 
                    || territory_map.at(y*sizeMap.x+(x+1)) == 0 
                    || territory_map.at(y*sizeMap.x+(x-1)) == 0
                    || territory_map.at((y-1)*sizeMap.x+x) == 3 
                    || territory_map.at((y+1)*sizeMap.x+x) == 3 
                    || territory_map.at(y*sizeMap.x+(x+1)) == 3 
                    || territory_map.at(y*sizeMap.x+(x-1)) == 3)
                    {
                        territory_map.at(y*sizeMap.x+x) = 3;
                        countUpdate++;
                    } 
                }  
            }
        }
    }

    //
    //SET TERRITORY
    for (int x = 0; x < sizeMap.x; ++x)
    {
        for (int y = 0; y < sizeMap.y; ++y)
        {
            if (territory_map.at(y*sizeMap.x+x) == 1)
            {
                territory_map.at(y*sizeMap.x+x) = 2;
            }  
        }
    }


    //Nb Walls
    int nbWalls = 0;
    for (int x = 0; x < sizeMap.x; ++x)
    {
        for (int y = 0; y < sizeMap.y; ++y)
        {
            if (wallsHere(walls, sf::Vector2f(x*32+16, y*32+16)) && territory_map.at(y*sizeMap.x+x)==4)
            {
                nbWalls++;
            }
        }
    }

    tileMap.load("ressources/tileset_territory.png", sf::Vector2u(32, 32), territory_map, sizeMap);
}

int Territory::countCaseEmpty()
{
    int countEmpty = 0;
    for (int x = 0; x < sizeMap.x; ++x)
    {
        for (int y = 0; y < sizeMap.y; ++y)
        {
            if (territory_map.at(y*sizeMap.x+x)==1){
                countEmpty++;
            }
        }
    }

    return countEmpty;
}

bool Territory::wallsHere(std::vector<Wall> walls, sf::Vector2f cursor)
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

void Territory::whereIsTerritory()
{
    for (int x = 0; x < sizeMap.x; ++x)
    {
        for (int y = 0; y < sizeMap.y; ++y)
        {
            if (territory_map.at(y*sizeMap.x+x) == 2)
            {
                std::cout << "Territory -> x,y : " << x << ", " << y << " -> " << territory_map.at(y*sizeMap.x+x) << std::endl;
            }
        }
    }
}

bool Territory::verificationTerritory(std::vector<Wall> walls)
{
    int count = 0;
    for (int x = 0; x < sizeMap.x; ++x)
    {
        for (int y = 0; y < sizeMap.y; ++y)
        {
            if (territory_map.at(y*sizeMap.x+x) == 2)
            {
                count++;
                //Test Water
                if (territory_map.at((y-1)*sizeMap.x+x) == 0 || territory_map.at((y+1)*sizeMap.x+x) == 0 || territory_map.at(y*sizeMap.x+(x+1)) == 0 || territory_map.at(y*sizeMap.x+(x-1)) == 0)
                {
                    return false;
                }
                //Test Earth
                if (territory_map.at((y-1)*sizeMap.x+x) == 1)
                {
                    if(!wallsHere(walls, sf::Vector2f(x*32+16, (y-1)*32+16))){
                        return false;
                    }
                }
                if (territory_map.at((y+1)*sizeMap.x+x) == 1)
                {
                    if(!wallsHere(walls, sf::Vector2f(x*32+16, (y+1)*32+16))){
                        return false;
                    }
                }
                if (territory_map.at(y*sizeMap.x+(x+1)) == 1)
                {
                    if(!wallsHere(walls, sf::Vector2f((x+1)*32+16, y*32+16))){
                        return false;
                    }
                }
                if (territory_map.at(y*sizeMap.x+(x-1)) == 1)
                {
                    if(!wallsHere(walls, sf::Vector2f((x-1)*32+16, y*32+16))){
                        return false;
                    }
                }
            }
        }
    }

    if (count == 0)
    {
        return false;
    }
    return true;
}


void Territory::makeBackUp()
{
    backup_territory_map = territory_map;
}

void Territory::useBackUp()
{
    territory_map = backup_territory_map;
}