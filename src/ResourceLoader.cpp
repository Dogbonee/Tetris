//
// Created by 24crickenbach on 3/26/2024.
//

#include "ResourceLoader.h"

#include <iostream>

using namespace GlobalResources;

void GlobalResources::LoadResources()
{
    if(!BlockFont.loadFromFile("../res/Pixeboy.ttf"))
    {
        std::cout<<"Could not load default font. Attempting to load fallback font\n";
        if(!BlockFont.loadFromFile("C:/Windows/Fonts/Ariel.ttf"))
        {
            std::cout<<"Could not load fallback font. Exiting...\n";
            exit(1);
        }
    }
}
