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

    void playGroundSound();

    void stopGroundSound();

private:
    const short int POS_X = 210;
    const short int POS_Y = 267;
    bool isPlay = 0;
    Mix_Chunk* breath = nullptr;
    Mix_Chunk* hit = nullptr;
    Mix_Chunk* drop = nullptr;
    Mix_Music* backgroundMusic = nullptr;

    SDL_Rect Mute;
    SDL_Rect Active;
};