#include "Land.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

bool Land::init()
{
    posLand.getPos(0, SCREEN_HEIGHT - LAND_HEIGHT);
    string back_path = LAND_PATH;
    if (isNULL())
    {
        if (Load(back_path.c_str(), 1 ))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

void Land::Free()
{
    free();
}

void Land::render()
{
    if (posLand.x > 0)
    {
        Render(posLand.x, posLand.y);
    }
    else if (posLand.x > -SCREEN_WIDTH && posLand.x <= 0)
    {
        Render(posLand.x, posLand.y);
        Render(posLand.x + SCREEN_WIDTH, posLand.y, 0, nullptr);
    }
    else
    {
        posLand.getPos(0, SCREEN_HEIGHT - LAND_HEIGHT+10);
        Render(posLand.x, posLand.y);
    }
}

void Land::update()
{
    posLand.x -= 3;
}
