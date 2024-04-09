//
// Created by 24crickenbach on 3/26/2024.
//

#include "ResourceLoader.h"

#include <iostream>

using namespace GlobalResources;

void GlobalResources::LoadResources()
{
    //Load all resource files necessary
    if(!BlockFont.loadFromFile("../res/Pixeboy.ttf"))
    {
        std::cout<<"Could not load default font. Attempting to load fallback font\n";
        if(!BlockFont.loadFromFile("C:/Windows/Fonts/Ariel.ttf"))
        {
            std::cout<<"Could not load fallback font. Exiting...\n";
            exit(1);
        }
    }

    if(!GameMusic.openFromFile("../res/Adventure.mp3"))
    {
        exit(1);
    }

    if(!TickBuffer.loadFromFile("../res/Tick.wav"))
    {
        exit(1);
    }
    if(!ClearBuffer.loadFromFile("../res/ClearLine.mp3"))
    {
        exit(1);
    }


}
