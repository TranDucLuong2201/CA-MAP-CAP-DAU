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
    bool checkMusic();
    void playGroundSound(short int mode);
    void stopGroundSound();
    void nextMusicTrack();

private:
    const short int POS_X = 210;
    const short int POS_Y = 460;
    Mix_Music* backgroundMusic;
    Mix_Chunk* breath;
    Mix_Chunk* hit;
    bool isPlay;
    SDL_Rect Active;
    SDL_Rect Mute;
    short int currentMusicTrack = 0;
};