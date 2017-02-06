#ifndef RAMPART_SHIPSMANAGER_H
#define RAMPART_SHIPSMANAGER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Ship.h"
#include "Exploser.h"

#include <cstdlib>
#include <iostream>

class ShipsManager : public Exploser {

    public:
        ShipsManager();

        inline void addShooter2Ships(Shooter *shooter) { shooters.push_back(shooter); };

        void placeShip(sf::Vector2f pos);
        inline void clearShips() { ships.clear(); };

        void drawShips(sf::RenderWindow & window);
        void shoot(size_t i, sf::Vector2f target);
        void moveOrShoot();
        bool AShipCanShoot(size_t i);
        void ChangeCanShoot(size_t i);
        void setCanShoot(size_t i);
        void setCanShootAll();

        sf::Vector2f getPositionShip(size_t i);
        void move(size_t i, sf::Vector2f pos);

        void notifyExplosion(void *from, sf::Vector2f pos, bool faction);

        size_t getSizeShips();

        bool shipsHere(sf::Vector2f cursor);

        bool AShipHasDestination(size_t i);

        void ShipSetDestination(size_t i, sf::Vector2f destination);
           
        sf::Vector2f getDestination(size_t i);

        void setNoneDestination(size_t i);

    private :

        std::vector<Shooter *> shooters;
        std::vector<Ship> ships;
        sf::Texture texture;
};


#endif //RAMPART_SHIPSMANAGER_H
