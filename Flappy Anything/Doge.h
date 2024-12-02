#pragma once

#include "Lib.h"
#include "Pipe.h"

using namespace std;

class Doge :LTexture
{
public:
    bool init(bool isDark);

    void render();

    void Free();

    void resetTime()
    {
        time = 0;
    }

    void fall();

    void update(short int pileWidth, short int pileHeight);
private:
    short int angle, time, x0;
    short int ahead = 0;
    string saved_path = "";
    Position posDoge;
};