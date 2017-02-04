//
// Created by xenoth on 04/02/17.
//

#ifndef RAMPART_CASTLE_H
#define RAMPART_CASTLE_H


#include "AbstractStaticEntity.h"

class Castle : public AbstractStaticEntity {

public:
    Castle(const sf::Texture &texture, const sf::Vector2f &pos);

};


#endif //RAMPART_CASTLE_H
