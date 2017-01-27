#ifndef RAMPART_EXPLOSABLE_H
#define RAMPART_EXPLOSABLE_H

#include <vector>
#include "Exploser.h"

class Explosable {

    public :
        void explose(void *from, sf::Vector2f pos, bool faction);

        inline void addExploser(Exploser *exploser) { explosers.push_back(exploser); };
        void removeExploser(Exploser *exploser);

    private:
        std::vector<Exploser*> explosers;
};


#endif
