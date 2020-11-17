#pragma once

#include <SDL2/SDL.h>

class GameController
{
public:
	GameController();

	float getXAxis();
	float getYAxis();

	~GameController();

private:
	SDL_GameController* controller;
};

