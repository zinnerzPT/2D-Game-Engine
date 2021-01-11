#include "GameController.h"
#include <SDL2/SDL_gamecontroller.h>

//FOR DEBUG PURPOSES ONLY
#include <iostream>

#define MAX_AXIS 32767.0f

SDL_GameController* controller;

GameController::GameController()
{
	controller = nullptr;
	int i;

	for (i = 0; i < SDL_NumJoysticks(); ++i) 
	{
		if (SDL_IsGameController(i)) 
		{

			//std::cout << "Index '" << i << "' is a compatible controller, named '" << SDL_GameControllerNameForIndex(i) << "'" << std::endl;
			controller = SDL_GameControllerOpen(i);
			isDetected = true;
		}
		else 
		{
			//std::cout << "Index '" << i << "' is not a compatible controller." << std::endl;
			isDetected = false;
		}
	}
}


// Game controller movement
float GameController::getXAxis() 
{
	return SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) / MAX_AXIS;
}

float GameController::getYAxis() 
{
	return SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) / MAX_AXIS;
}

bool GameController::getButtonA()
{
	return SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);
}

GameController::~GameController() 
{

	SDL_GameControllerClose(controller);

}