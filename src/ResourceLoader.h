//
// Created by 24crickenbach on 3/26/2024.
//

#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H
#include <SFML/Audio.hpp>

#include "System.h"

namespace GlobalResources {
    inline sf::Font BlockFont;
    inline sf::Music GameMusic;
    inline sf::SoundBuffer TickBuffer;
    inline sf::SoundBuffer ClearBuffer;
    void LoadResources();
}


#endif //RESOURCELOADER_H
