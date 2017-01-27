#ifndef RAMPART_EXPLOSER_H
#define RAMPART_EXPLOSER_H

#include "Shootable.h"

class Exploser {
    public:
        virtual void notifyExplosion(void *from, sf::Vector2f pos, bool faction) = 0;
};


#endif
