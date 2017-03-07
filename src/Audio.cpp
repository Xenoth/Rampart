#include <iostream>
#include "Audio.h"

Audio::Audio()
{
    buffer1.loadFromFile("../ressources/explosion.wav");
    buffer2.loadFromFile("../ressources/shoot.wav");
    explosion.setBuffer(buffer1);
    shoot.setBuffer(buffer2);

    explosion.setVolume(20);
    shoot.setVolume(70);
}

void Audio::pause()
{
    music.pause();
    explosion.stop();
    shoot.stop();
}

void Audio::resume()
{
    music.play();
}

void Audio::playMusic() {
    music.openFromFile("../ressources/skyrim.wav");
    music.setLoop(true);
    music.play();
}

void Audio::playExplosion() {
    explosion.play();
    std::cout << "Playing explosion" << std::endl;
}

void Audio::playShoot() {
    shoot.play();
    std::cout << "Playing shoot" << std::endl;
}