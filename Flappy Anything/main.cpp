#include "Game.h"
#include "Lib.h"
#include <time.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h> // Thêm thư viện SDL_mixer

const short int FPS = 90;
const short int frameDelay = 900 / FPS;

using namespace std;

int main(int argc, char** argv)  // Fixed main function signature
{
    Uint32 frameStart;
    short int frameTime;
    Game g;
    bool isMenu = 0;
    bool isPause = 0;
    bool isSound = 1;
    short mode = 0;
    short pet = 0;

    while (!g.isQuit()) {
        frameStart = SDL_GetTicks();
        if (isSound) g.sound.playGroundSound();
        if (g.isDie()) {
            if (isMenu) {
                g.sound.playHit();
                g.shiba.render();
            }
            g.userInput.Type = Game::input::NONE;
            while (g.isDie() && !g.isQuit()) {
                g.takeInput();
                if (isMenu == 1 && g.userInput.Type == Game::input::PLAY) {
                    if (g.checkReplay()) {
                        isMenu = 0;
                    }
                    g.userInput.Type = Game::input::NONE;
                }
                if (!mode) g.renderBackground();
                else if(mode == 1) g.renderBackgroundNight();
                else if(mode == 2) g.renderBackgroundSnow();
				else mode = 0;
                g.pipe.render();
                g.land.render();
                if (isMenu) {
                    g.shiba.render();
                    g.shiba.fall();
                    g.renderGameOver();
                    g.renderMedal();
                    g.renderScoreSmall();
                    g.renderBestScore();
                    g.replay();
                }
                else {
                    g.pipe.init();
                    g.shiba.init(mode);
                    g.shiba.render();
                    g.renderMessage();
                    if (g.userInput.Type == Game::input::PLAY) {
                        g.Restart();
                        isMenu = 1;
                        g.userInput.Type = Game::input::NONE;
                    }
                    g.land.update();
                }
                g.display();
            }
            g.pipe.init();
        }
        else {
            g.takeInput();

            if (g.userInput.Type == Game::input::PAUSE) {
                isPause = abs(1 - isPause);
                g.userInput.Type = Game::input::NONE;
            }

            if (isPause == 0 && g.userInput.Type == Game::input::PLAY) {
                if (isSound) g.sound.playBreath();
                g.shiba.resetTime();
                g.userInput.Type = Game::input::NONE;
            }

            if (!mode) g.renderBackground();
            else if (mode == 1) g.renderBackgroundNight();
            else if (mode == 2) g.renderBackgroundSnow();
            else mode = 0;
            g.pipe.render();
            g.land.render();
            g.shiba.render();
            g.renderScoreLarge();

            if (!isPause) {
                g.shiba.update(g.getPipeWidth(), g.getPipeHeight());
                g.pipe.update();
                g.land.update();
                g.pause();
            }
            else {
                g.resume();
                g.renderPauseTab();
                g.renderScoreSmall();
                g.renderBestScore();
                g.replay();
                g.sound.renderSound();
                if (!mode) g.lightTheme(); else if (mode == 1) g.darkTheme();
				else if (mode == 2) g.noelTheme();
				else mode = 0;
				g.iconPet(pet);
                g.nextButton();
                g.nextPets();
                if (g.userInput.Type == Game::input::PLAY) {
                    if (g.checkReplay()) {
                        isPause = 0;
                    }
                    else if (g.sound.checkSound()) {
                        isSound = abs(1 - isSound);
                        if (isSound == 0) g.sound.stopGroundSound();
                        if (isSound == 1) g.sound.playGroundSound();
                    }
                    else if (g.changeTheme()) {
                        mode += 1;
					}
                    else if (g.changePet()) {
						if (pet > 8) pet = 0;
                        pet += 1;
                        g.shiba.init(pet);
                    }
                    g.userInput.Type = Game::input::NONE;
                }
            }
            g.display();
        }

        // Limit FPS
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    return 0;
}