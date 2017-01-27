#ifndef RAMPART_AUDIO_H
#define RAMPART_AUDIO_H

#include "SFML/Audio.hpp"
#include "Exploser.h"
#include "Shooter.h"

class Audio : public Shooter, public Exploser
{
    public :

        Audio();

        void pause();
        void resume();

        void playMusic();
        void playExplosion();
        void playShoot();

        inline void notifyExplosion(void *from, sf::Vector2f pos, bool faction) { playExplosion(); };
        inline void notifyShoot(sf::Vector2f pos, sf::Vector2f target, bool faction, void *from) { playShoot(); };

    private :

        sf::SoundBuffer buffer1, buffer2;
        sf::Sound explosion;
        sf::Sound shoot;

        sf::Music music;


};


#endif //RAMPART_AUDIO_H
