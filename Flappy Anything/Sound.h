#pragma once

#include <SDL_mixer.h>
#include <string>
#include "Lib.h"
#include "utils.h"

using namespace std;

class Sound :LTexture
{
public:
    bool init();

    void Free();

    void playBreath();

    void playHit();

    void renderSound();

    bool checkSound();

private:
    const short int POS_X = 107;
    const short int POS_Y = 267;
    bool isPlay = 0;
    Mix_Chunk* breath = NULL;
    Mix_Chunk* hit = NULL;
    Mix_Chunk* drop = NULL;
    SDL_Rect Mute;
    SDL_Rect Active;
};