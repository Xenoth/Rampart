#include "Explosable.h"
#include <iostream>

void Explosable::explose(void *from, sf::Vector2f pos, bool faction) {
	std::cout << "explose (Explosable.h) : from = " << from << std::endl;
    std::cout << "\tExplosers number = " << explosers.size() << std::endl;
        for (size_t i = 0; i < explosers.size(); i++)
            explosers.at(i)->notifyExplosion(from, pos, faction);
}


void Explosable::removeExploser(Exploser *exploser){
    for(size_t i=0; i<explosers.size(); i++) {
        if (explosers.at(i) == exploser) {
            explosers.erase(explosers.begin() + i);
            break;
        }
    }
}