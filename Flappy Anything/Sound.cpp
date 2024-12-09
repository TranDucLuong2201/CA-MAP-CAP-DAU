#include "Sound.h"
#include <stdio.h>
#include <iostream>
#include <string>

bool Sound::init()
{
    string breath_path = BREATH_PATH;
    string hit_path = HIT_PATH;
    string sound_path = SOUND_PATH;
    string ground_path = SOUND_PICKELBALL_PATH;
    bool success = true;

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
            success = false;
        }

        breath = Mix_LoadWAV(breath_path.c_str());
        if (breath == NULL)
        {
            printf("Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError());
            success = false;
        }

        hit = Mix_LoadWAV(hit_path.c_str());
        if (hit == NULL)
        {
            printf("Failed to load chord! SDL_mixer Error: %s\n", Mix_GetError());
            success = false;
        }

        backgroundMusic = Mix_LoadMUS(ground_path.c_str());
        if (backgroundMusic == nullptr)
        {
            printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
            success = false;
        }

        if (!Load(sound_path))
        {
            return false;
        }

        Active.x = 0; Active.y = 0; Active.w = getWidth(); Active.h = getHeight() / 2;
        Mute.x = 0; Mute.y = getHeight() / 2; Mute.w = getWidth(); Mute.h = getHeight() / 2;
        isPlay = true;
    }
    return success;
}

void Sound::Free()
{
    free();

    Mix_FreeChunk(breath);
    breath = NULL;
    Mix_FreeChunk(hit);
    hit = NULL;

    Mix_Quit();
}

void Sound::playBreath()
{
    if (isPlay)
    {
        Mix_PlayChannel(-1, breath, 0);
    }
}

void Sound::playHit()
{
    if (isPlay)
    {
        Mix_PlayChannel(-1, hit, 0);
    }
}

void Sound::renderSound()
{
    if (isPlay)
    {
        Render(POS_X, POS_Y, 0, &Active);
    }
    else
    {
        Render(POS_X, POS_Y, 0, &Mute);
    }
}

bool Sound::checkSound()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x > POS_X && x < POS_X + getWidth() &&
        y > POS_Y && y < POS_Y + getHeight())
    {
        isPlay = !isPlay;
        return true;
    }
    return false;
}

bool Sound::checkMusic()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x > 298 && x < 369 + 13 &&
        y > 450 && y < 450 + 13)
    {
        return true;
    }
    return false;
}

void Sound::playGroundSound(short int mode)
{
    const short int NUM_MUSIC = 5;
    const string ground_path[NUM_MUSIC] = {
        SOUND_PICKELBALL_PATH,
        SOUND_TINHTU_PATH,
        SOUND_NOEL_PATH,
        SOUND_NIGHT_PATH,
        SOUND_MONO_PATH
    };
    backgroundMusic = Mix_LoadMUS(ground_path[mode].c_str());
    if (backgroundMusic != NULL && Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(backgroundMusic, -1);
    }
}

void Sound::stopGroundSound()
{
    if (Mix_PlayingMusic() != 0)
    {
        Mix_HaltMusic();
    }
}

void Sound::nextMusicTrack()
{
    const short int NUM_MUSIC = 5;
    const string ground_path[NUM_MUSIC] = {
        SOUND_PICKELBALL_PATH,
        SOUND_TINHTU_PATH,
        SOUND_NOEL_PATH,
        SOUND_NIGHT_PATH,
        SOUND_MONO_PATH
    };
    currentMusicTrack = (currentMusicTrack + 1) % NUM_MUSIC;
    stopGroundSound();
    backgroundMusic = Mix_LoadMUS(ground_path[currentMusicTrack].c_str());
    if (backgroundMusic != NULL)
    {
        Mix_PlayMusic(backgroundMusic, -1);
    }
}