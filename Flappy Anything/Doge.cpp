#include "Doge.h"
#include <stdio.h>
#include <iostream>

bool Doge::init(short pet)
{
    const int NUM_CHARACTERS = 9;
    const string character_paths[NUM_CHARACTERS] = {
        BEE_PATH, FISH_PATH, DUCK_PATH,
        FROGE_PATH, BIRD_PATH, START_PATH,
        MONSTER_PATH,VIRUS_PATH,SHIBA_PATH
    };

    if (pet < 0 || pet >= NUM_CHARACTERS) {
        std::cerr << "Invalid character selection." << std::endl;
        return false;
    }

    string selected_path = character_paths[pet];
    if (saved_path == selected_path)
    {
        posDoge.getPos(75, SCREEN_HEIGHT / 2 - 10);
        ahead = 0;
        angle = 0;
    }
    if (isNULL() || saved_path != selected_path)
    {
        saved_path = selected_path;
        if (Load(selected_path.c_str(), 1))
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

void Doge::Free()
{
    free();
}

void Doge::render()
{
    Render(posDoge.x, posDoge.y, angle);
}

void Doge::fall()
{
    if (die && posDoge.y < SCREEN_HEIGHT - LAND_HEIGHT - SHIBA_HEIGHT - 5)
    {
        if (time == 0)
        {
            x0 = posDoge.y;
            angle = -25;
        }
        else if (angle < 70 && time > 30)
        {
            angle += 3;
        }

        if (time >= 0)
        {
            posDoge.y = x0 + time * time * 0.18 - 7.3 * time;
            time++;
        }
    }
    else return;
}

void Doge::update(short int pipeWidth, short int pipeHeight)
{
    if (!die)
    {
        if (time == 0)
        {
            x0 = posDoge.y;
            angle = -25;
        }
        else if (angle < 70 && time > 30)
        {
            angle += 3;
        }

        if (time >= 0)
        {
            posDoge.y = x0 + time * time * 0.18 - 7.3 * time;
            time++;
        }

        if ((posDoge.x + getWidth() > posPipe[ahead].x + 5) && (posDoge.x + 5 < posPipe[ahead].x + pipeWidth) &&
            (posDoge.y + 5 < posPipe[ahead].y + pipeHeight || posDoge.y + getHeight() > posPipe[ahead].y + pipeHeight + PIPE_SPACE + 5))
        {
            die = true;
        }
        else if (posDoge.x > posPipe[ahead].x + pipeWidth)
        {
            ahead = (ahead + 1) % TOTAL_PIPE;
            score++;
        }

        if (posDoge.y > SCREEN_HEIGHT - LAND_HEIGHT - SHIBA_HEIGHT - 5 || posDoge.y < -10)
        {
            die = true;
        }
    }
}