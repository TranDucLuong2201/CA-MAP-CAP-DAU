#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <stdio.h>

#include "utils.h"

class Position
{
public:
	short int x, y, angle, state;
	void getPos(const short int x, const short int y);
};

class LTexture
{
public:
	LTexture();

	~LTexture() {}

	bool isNULL();
	bool Load(std::string path, double scale = SCALE_VALUE);

	short int getWidth();
	short int getHeight();

	void free();
	void Render(
		short int x,
		short int y,
		short int angle = DEFAULT_SCALE_VALUE,
		SDL_Rect* clip = nullptr,
		SDL_RendererFlip flip = SDL_FLIP_NONE);
public:
	SDL_Texture* Texture;
	short int tWidth;
	short int tHeight;
public:
	static SDL_Window* gWindow;
	static SDL_Renderer* gRenderer;
	static SDL_Event event;
	static bool quit;
	static bool die;
	static short int score;
};

