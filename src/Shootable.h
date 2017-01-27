#ifndef RAMPART_SHOOTABLE_H
#define RAMPART_SHOOTABLE_H

#include <cstdlib>
#include <vector>
#include "Shooter.h"

class Shootable {

    public:
        void shoot(sf::Vector2f pos, sf::Vector2f target, bool faction, void *from);

        inline void addShooter(Shooter *shooter) { shooters.push_back(shooter); };
        void removeShooter(Shooter *shooter);


private:
        std::vector<Shooter*> shooters;
};


#endif
