#include "Game.h"
#include "Lib.h"
#include "utils.h"
#include <iostream>

void Game::takeInput()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			userInput.Type = input::QUIT;
			quit = true;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN ||
			(event.type == SDL_KEYDOWN &&
				(event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP) && event.key.repeat == 0))
		{
			userInput.Type = input::PLAY;
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE && event.key.repeat == 0)
		{
			userInput.Type = input::PAUSE;
		}
	}
}

Game::Game()
{
	initGraphic();
	pipe.init();
	land.init();
	sound.init();
}

Game::~Game()
{
	shiba.Free();
	pipe.Free();
	land.Free();
	sound.Free();
	free();
	releaseGraphic();
}

void Game::releaseGraphic()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool Game::initGraphic()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		gWindow = SDL_CreateWindow("Flappy Doge", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void Game::display()
{
	SDL_RenderPresent(gRenderer);
	SDL_RenderClear(gRenderer);
}

void Game::renderScoreSmall()
{
	string s = to_string(score);
	signed char len = s.length();
	LTexture image;

	for (signed char i = len - 1; i >= 0; i--)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load(ONE_PATH_SMALL, scaleNumberS);
		}
		else if (number == 2)
		{
			image.Load(TWO_PATH_SMALL, scaleNumberS);
		}
		else if (number == 3)
		{
			image.Load(THREE_PATH_SMALL, scaleNumberS);
		}
		else if (number == 4)
		{
			image.Load(FOUR_PATH_SMALL, scaleNumberS);
		}
		else if (number == 5)
		{
			image.Load(FIVE_PATH_SMALL, scaleNumberS);
		}
		else if (number == 6)
		{
			image.Load(SIX_PATH_SMALL, scaleNumberS);
		}
		else if (number == 7)
		{
			image.Load(SEVEN_PATH_SMALL, scaleNumberS);
		}
		else if (number == 8)
		{
			image.Load(EIGHT_PATH_SMALL, scaleNumberS);
		}
		else if (number == 9)
		{
			image.Load(NINE_PATH_SMALL, scaleNumberS);
		}
		else
		{
			image.Load(ZERO_PATH_SMALL, scaleNumberS);
		}
		image.Render(215 - image.getWidth() * (len - i - 1) * 0.75 - 5 * (len - i - 1), 355);
	}
	image.free();
}

void Game::renderScoreLarge()
{
	string s = to_string(score);
	signed char len = s.length();
	LTexture image;

	for (signed char i = 0; i < len; i++)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load(ONE_PATH_LARGE, SCALE_VALUE);
		}
		else if (number == 2)
		{
			image.Load(TWO_PATH_LARGE, SCALE_VALUE);
		}
		else if (number == 3)
		{
			image.Load(THREE_PATH_LARGE, SCALE_VALUE);
		}
		else if (number == 4)
		{
			image.Load(FOUR_PATH_LARGE, SCALE_VALUE);
		}
		else if (number == 5)
		{
			image.Load(FIVE_PATH_LARGE, SCALE_VALUE);
		}
		else if (number == 6)
		{
			image.Load(SIX_PATH_LARGE, SCALE_VALUE);
		}
		else if (number == 7)
		{
			image.Load(SEVEN_PATH_LARGE, SCALE_VALUE);
		}
		else if (number == 8)
		{
			image.Load(EIGHT_PATH_LARGE, SCALE_VALUE);
		}
		else if (number == 9)
		{
			image.Load(NINE_PATH_LARGE, SCALE_VALUE);
		}
		else
		{
			image.Load(ZERO_PATH_LARGE, SCALE_VALUE);
		}
		image.Render((SCREEN_WIDTH - (image.getWidth() * len + (len - 1) * 10)) / 2 + (i + 30) * i, 120);
	}
	image.free();
}

void Game::renderBestScore()
{
	ifstream fileIn(BEST_SCORE_DATA_FILE);
	fileIn >> bestScore;
	ofstream fileOut(BEST_SCORE_DATA_FILE, ios::trunc);

	if (score > bestScore)
	{
		bestScore = score;
	}
	string s = to_string(bestScore);
	signed char len = s.length();
	LTexture image;

	for (signed char i = len - 1; i >= 0; i--)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load(ONE_PATH_SMALL, scaleNumberS);
		}
		else if (number == 2)
		{
			image.Load(TWO_PATH_SMALL, scaleNumberS);
		}
		else if (number == 3)
		{
			image.Load(THREE_PATH_SMALL, scaleNumberS);
		}
		else if (number == 4)
		{
			image.Load(FOUR_PATH_SMALL, scaleNumberS);
		}
		else if (number == 5)
		{
			image.Load(FIVE_PATH_SMALL, scaleNumberS);
		}
		else if (number == 6)
		{
			image.Load(SIX_PATH_SMALL, scaleNumberS);
		}
		else if (number == 7)
		{
			image.Load(SEVEN_PATH_SMALL, scaleNumberS);
		}
		else if (number == 8)
		{
			image.Load(EIGHT_PATH_SMALL, scaleNumberS);
		}
		else if (number == 9)
		{
			image.Load(NINE_PATH_SMALL, scaleNumberS);
		}
		else
		{
			image.Load(ZERO_PATH_SMALL, scaleNumberS);
		}
		image.Render(335 - image.getWidth() * (len - i - 1) * 0.75 - 5 * (len - i - 1), 355);
	}
	image.free();

	fileOut << bestScore;
	fileIn.close();
	fileOut.close();
}

void Game::renderMessage()
{
	LTexture image;
	image.Load(MESSAGE_PATH, SCALE_VALUE);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 180);
	image.free();
}

void Game::renderBackground()
{
	LTexture image;
	image.Load(BACKGROUND_PATH, SCALE_VALUE);
	image.Render(0, 0);
	image.free();
}

void Game::renderBackgroundNight()
{
	LTexture image;
	image.Load(BACKGROUND_NIGHT_PATH, SCALE_VALUE);
	image.Render(0, 0);
	image.free();
}

void Game::renderBackgroundSnow()
{
	LTexture image;
	image.Load(BACKGROUND_SNOW_PATH, SCALE_VALUE);
	image.Render(0, 0);
	image.free();
}

void Game::renderLand()
{
	LTexture image;
	image.Load(LAND_PATH, SCALE_VALUE);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, SCREEN_HEIGHT - image.getHeight());
	image.free();
}

void Game::resume()
{
	LTexture image;
	image.Load(RESUME_PATH, SCALE_VALUE);
	image.Render(SCREEN_WIDTH - 50, 20);
	image.free();
}

void Game::pause()
{
	LTexture image;
	image.Load(PAUSE_PATH, SCALE_VALUE);
	image.Render(SCREEN_WIDTH - 50, 20);
	image.free();
}

void Game::renderPauseTab()
{
	LTexture image;
	image.Load(PAUSE_TAB_PATH, SCALE_VALUE );
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 220);
	image.free();
}

void Game::lightTheme()
{
	LTexture image;
	image.Load(LIGHT_MODE, SCALE_SHIBA);
	image.Render(205, 555);
	image.free();
}

void Game::darkTheme()
{
	LTexture image;
	image.Load(DARK_MODE, SCALE_SHIBA);
	image.Render(205, 555);
	image.free();
}

void Game::noelTheme()
{
	LTexture image;
	image.Load(NOEL_MODE, SCALE_SHIBA);
	image.Render(205, 555);
	image.free();
}
void Game::iconPet(short pet)
{
	string path = "";
	switch (pet)
	{
	case 0:
		path = BEE_PATH;
		break;
	case 1:
		path = FISH_PATH;
		break;
	case 2:
		path = DUCK_PATH;
		break;
	case 3:
		path = FROGE_PATH;
		break;
	case 4:
		path = BIRD_PATH;
		break;
	case 5:
		path = START_PATH;
		break;
	case 6:
		path = MONSTER_PATH;
		break;
	case 7:
		path = VIRUS_PATH;
		break;
	case 8:
		path = SHIBA_PATH;
		break;
	default:
		path = SHIBA_PATH;
		break;
	}
	LTexture image;
	image.Load(path, SCALE_SHIBA);
	image.Render(320, 550);
	image.free();
}
void Game::nextButton()
{
	LTexture image;
	image.Load(NEXT_RIGHT_PATH, SCALE_VALUE);
	image.Render(249, 560);
	image.Load(NEXT_LEFT_PATH, SCALE_VALUE);
	image.Render(188, 560);
	image.free();
}
void Game::nextPets()
{
	LTexture image;
	image.Load(NEXT_RIGHT_PATH, SCALE_VALUE);
	image.Render(369, 560);
	image.Load(NEXT_LEFT_PATH, SCALE_VALUE);
	image.Render(298, 560);
	image.free();
}

bool Game::changePet()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (((x > 369 && x < 369 + 13) || (x > 188 && x < 188 + 13)) && (y > 560 && y < 560 + 16))
	{
		return true;
	}
	return false;
}

bool Game::changeTheme()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (((x > 249 && x < 249 + 13) || (x > 188 && x < 188 + 13)) && (y > 560 && y < 560 + 16))
	{
		return true;
	}
	return false;
}

bool Game::changeMusic()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (((x > 298 && x < 298 + 13) || (x > 369 && x < 369 + 13)) && (y > 460 && y < 460 + 16))
	{
		return true;
	}
	return false;
}

void Game::nextMusic()
{
	LTexture image;
	image.Load(NEXT_RIGHT_PATH, SCALE_VALUE);
	image.Render(369, 460);
	image.Load(NEXT_LEFT_PATH, SCALE_VALUE);
	image.Render(298, 460);
	image.free();
	image.Load(MUSIC_PATH, SCALE_VALUE);
	image.Render(315, 450);
}

void Game::renderLand(short mode)
{
	LTexture image;
	switch (mode) {
	case 0:
		image.Load(LAND_PATH, SCALE_VALUE);
		break;
	case 1:
		image.Load(LAND_DARK_PATH, SCALE_VALUE);
		break;
	case 2:
		image.Load(LAND_NOEL_PATH, SCALE_VALUE);
		break;
	default:
		image.Load(LAND_PATH, SCALE_VALUE);
		break;
	}
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, SCREEN_HEIGHT - image.getHeight());
	image.free();
}

void Game::renderGameOver()
{
	LTexture image;
	image.Load(GAMEOVER_PATH, SCALE_VALUE);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 100);
	image.free();
}

void Game::renderMedal()
{
	LTexture image;

	if (score > 20 && score <= 50)
	{
		image.Load(SILVER_PATH, scaleNumberS);
	}
	else if (score > 50)
	{
		image.Load(GOLD_PATH, scaleNumberS);
	}
	else
	{
		image.Load(HONOR_PATH, scaleNumberS);
	}
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 380);

	image.free();
}

void Game::replay()
{
	LTexture image;
	image.Load(REPLAY_PATH, SCALE_VALUE);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 650);
	image.free();
}

bool Game::checkReplay()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x > (SCREEN_WIDTH - 100) / 2 && x < (SCREEN_WIDTH + 100) / 2 && y > 650 && y < 650 + 60)
	{
		return true;
	}
	return false;
}

void Game::Restart()
{
	die = false;
	score = 0;
	shiba.resetTime();
}