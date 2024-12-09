#pragma once

#include "Doge.h"
#include "Pipe.h"
#include "Land.h"
#include "Sound.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Game :LTexture
{
public:
    struct input
    {
        enum type { QUIT, PLAY, NONE, PAUSE };
        type Type;
    };
    input userInput;
    Doge shiba;
    Pipe pipe;
    Sound sound;
    Land land;
public:
    Game();

    ~Game();

    bool initGraphic();

    bool isQuit()
    {
        return quit;
    }

    bool isDie()
    {
        return die;
    }

    int getPipeWidth()
    {
        return pipe.width();
    }

    int getPipeHeight()
    {
        return pipe.height();
    }

    void takeInput();

    void display();

    void releaseGraphic();

    void renderScoreSmall();

    void renderScoreLarge();

    void renderBestScore();

    void renderMessage();

    void renderBackground();

    void renderBackgroundNight();

	void renderBackgroundSnow();

    void renderLand();

    void resume();

    void pause();

    void renderPauseTab();

    void lightTheme();

    void darkTheme();

	void noelTheme();

	void iconPet(short pet);

    void nextButton();

	void nextPets();

    bool changeTheme();

	bool changePet();

    void renderGameOver();

    void renderMedal();

    void replay();

    bool checkReplay();

    void Restart();

private:
    const double scaleNumberS = 0.75;
    short int bestScore;
};