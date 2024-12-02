#pragma once

#include "Lib.h"
#include <vector>

using namespace std;

class Land : LTexture
{
public:
    bool init();

    void Free();

    void render();

    void update();

private:
    Position posLand;
};