#include "GameController.h"

GameController::GameController()
{
	controller = nullptr; 
	int i;

	for (i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {

			//std::cout << "Index '" << i << "' is a compatible controller, named '" << SDL_GameControllerNameForIndex(i) << "'" << std::endl;
			controller = SDL_GameControllerOpen(i);

		}
		else {
			//std::cout << "Index '" << i << "' is not a compatible controller." << std::endl;
		}
	}
}


// Game controller movement
float GameController::getXAxis() {
	return SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
}

float GameController::getYAxis() {
	return SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
}

GameController::~GameController() {
	SDL_GameControllerClose(controller);
}