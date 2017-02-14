//
// Created by xenoth on 18/01/17.
//

#include "Territory.h"

Territory::Territory() {}

void Territory::loadTileMap(std::vector<uint8_t> tiles, sf::Vector2u mapSize){
    territory_map.clear();
    this->sizeMap = mapSize;
    for (size_t i = 0; i < tiles.size(); i++){
        if(tiles.at(i) != 0){
            territory_map.push_back(1);
            backup_territory_map.push_back(1);
        } else{
            territory_map.push_back(0);
            backup_territory_map.push_back(0);
        }
    }

    tileMap.load("ressources/tileset_territory.png", sf::Vector2u(32, 32), territory_map, sizeMap);

}

void Territory::updateTileMap(){
    tileMap.load("ressources/tileset_territory.png", sf::Vector2u(32, 32), territory_map, sizeMap);
}
//sideBySide

void Territory::calculateTerritory(std::vector<Wall> walls, sf::Vector2u castlePosition, bool isCastle){
    //std::cout << "REMPLISSAGE"  << std::endl;
    if (isCastle)
    {
        std::cout << "\tCastle"  << std::endl;
        calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x+1, (uint)castlePosition.y), false);
        calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x-1, (uint)castlePosition.y), false);
        calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x, (uint)castlePosition.y+1), false);
        calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x, (uint)castlePosition.y-1), false);
    }
    if (territory_map.at(castlePosition.y*sizeMap.x+castlePosition.x) == 1)
    {
        //std::cout << "\tHerbe"  << std::endl;
        if (!wallsHere(walls, sf::Vector2f(castlePosition.x*32+16, castlePosition.y*32+16)))
        {
            //std::cout << "\tPas de Mur"  << std::endl;
            territory_map.at(castlePosition.y*sizeMap.x+castlePosition.x)=2;
            calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x+1, (uint)castlePosition.y), false);
            calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x-1, (uint)castlePosition.y), false);
            calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x, (uint)castlePosition.y+1), false);
            calculateTerritory(walls, sf::Vector2u((uint)castlePosition.x, (uint)castlePosition.y-1), false);
        }
    }
    tileMap.load("ressources/tileset_territory.png", sf::Vector2u(32, 32), territory_map, sizeMap);
}

void Territory::calculateNoTerritory(std::vector<Wall> walls){
    //TO DO
    std::cout << "\tSET WALLS" << std::endl;
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



    std::cout << "\tCALCULATE NO TERRITORY" << std::endl;
    int countUpdate = 1;
    while(countCaseEmpty()!=0 && countUpdate!=0){
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
                        //std::cout << "Territory -> x,y : " << x << ", " << y << " -> " << territory_map.at(y*sizeMap.x+x) << "\tnext to Water or 3"<< std::endl;
                    } 
                }  
            }
        }
        std::cout << "countUpdate : " << countUpdate << std::endl;
    }

    //

    std::cout << "\tSET TERRITORY" << std::endl;
    for (int x = 0; x < sizeMap.x; ++x)
    {
        for (int y = 0; y < sizeMap.y; ++y)
        {
            if (territory_map.at(y*sizeMap.x+x) == 1)
            {
                std::cout << "Territory -> x,y : " << x << ", " << y << std::endl;
                territory_map.at(y*sizeMap.x+x) = 2;
            }  
        }
    }


    //Nb Walls
    std::cout << "\tNB WALLS" << std::endl;
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
    std::cout << "NB WALLS : " << nbWalls << std::endl;
    tileMap.load("ressources/tileset_territory.png", sf::Vector2u(32, 32), territory_map, sizeMap);
}

int Territory::countCaseEmpty(){
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
    std::cout << "NB EMPTY : " << countEmpty << std::endl;
    return countEmpty;
}

bool Territory::wallsHere(std::vector<Wall> walls, sf::Vector2f cursor){
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
                //Territory
                std::cout << "Territory -> x,y : " << x << ", " << y << " -> " << territory_map.at(y*sizeMap.x+x) << std::endl;
            }
        }
    }
}

bool Territory::verificationTerritory(std::vector<Wall> walls){
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
                    std::cout << "Territory -> x,y : " << x << ", " << y << " -> " << territory_map.at(y*sizeMap.x+x) << "\tnext to Water"<< std::endl;
                    return false;
                }
                //Test Earth
                if (territory_map.at((y-1)*sizeMap.x+x) == 1)
                {
                    if(!wallsHere(walls, sf::Vector2f(x*32+16, (y-1)*32+16))){
                        std::cout << "Territory -> x,y(-1) : " << x << ", " << y << " -> " << territory_map.at(y*sizeMap.x+x) << "\tnext to Earth"<< std::endl;
                        return false;
                    }
                }
                if (territory_map.at((y+1)*sizeMap.x+x) == 1)
                {
                    if(!wallsHere(walls, sf::Vector2f(x*32+16, (y+1)*32+16))){
                        std::cout << "Territory -> x,y(-1) : " << x << ", " << y << " -> " << territory_map.at(y*sizeMap.x+x) << "\tnext to Earth"<< std::endl;
                        return false;
                    }
                }
                if (territory_map.at(y*sizeMap.x+(x+1)) == 1)
                {
                    if(!wallsHere(walls, sf::Vector2f((x+1)*32+16, y*32+16))){
                        std::cout << "Territory -> x,y(-1) : " << x << ", " << y << " -> " << territory_map.at(y*sizeMap.x+x) << "\tnext to Earth"<< std::endl;
                        return false;
                    }
                }
                if (territory_map.at(y*sizeMap.x+(x-1)) == 1)
                {
                    if(!wallsHere(walls, sf::Vector2f((x-1)*32+16, y*32+16))){
                        std::cout << "Territory -> x,y(-1) : " << x << ", " << y << " -> " << territory_map.at(y*sizeMap.x+x) << "\tnext to Earth"<< std::endl;
                        return false;
                    }
                }
            }
        }
    }
    std::cout << "Count : " << count << std::endl;
    if (count == 0)
    {
        return false;
    }
    return true;
}


void Territory::makeBackUp(){
    backup_territory_map = territory_map;
}

void Territory::useBackUp(){
    territory_map = backup_territory_map;
}