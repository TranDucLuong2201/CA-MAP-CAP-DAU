#pragma once

#include "Lib.h"
#include <iostream>
#include <vector>

using namespace std;

extern vector<Position> posPipe;

class Pipe :LTexture
{
private:
    const short int randMin = -373 + 30;
    const short int randMax = SCREEN_HEIGHT - LAND_HEIGHT - 373 - PIPE_DISTANCE - 30;
public:
    bool init();

    void Free();

    void render();

    void update();

    short int width() { return getWidth(); }

    short int height() { return getHeight(); }
};