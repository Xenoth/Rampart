#ifndef RAMPART_SHOOTER_H
#define RAMPART_SHOOTER_H

#include <SFML/System/Vector2.hpp>

class Shooter {
    public:
        virtual void notifyShoot(sf::Vector2f pos, sf::Vector2f target, bool faction, void *from) = 0;
};


#endif
