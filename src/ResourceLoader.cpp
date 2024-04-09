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
        if(!BlockFont.loadFromFile("./res/Pixeboy.ttf"))
        {
            exit(1);
        }
    }
}
