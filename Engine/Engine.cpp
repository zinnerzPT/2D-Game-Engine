#include "Engine.h"
#include <iostream>
#include <SDL2/SDL.h>


void Engine::Start()
{
	std::cout << "Engine started!" << std::endl;

	// VERY PLACEHOLDER
	RunLogics();
}

int Engine::RunLogics() {

		SDL_Window* window = nullptr;
		SDL_Texture* currentTexture = nullptr;
		SDL_Texture* background = nullptr;
		SDL_Renderer* renderTarget = nullptr;
		SDL_Rect playerRect;
		SDL_Rect playerPosition;
		playerPosition.x = playerPosition.y = 0;
		playerPosition.w = playerPosition.h = 32;
		float playerPosX, playerPosY;
		playerPosX = playerPosY = 0.0f;
		int textureWidth, textureHeight;
		int frameWidth, frameHeight;

		float frameTime = 0;
		int prevTime = 0;
		int currentTime = 0;
		float deltaTime = 0;

		float moveSpeed = 200.0f;
		const Uint8* keyState;

		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cout << "Video Initialization Error: " << SDL_GetError() << std::endl;
			return 1;
		}

		window = SDL_CreateWindow("AGPT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
		if (window == NULL) {
			std::cout << "Window Creation Error: " << SDL_GetError() << std::endl;
			return 2;
		}

		renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		//currentTexture = LoadTexture("../graphics/drone.bmp", renderTarget);
		//background = LoadTexture("../graphics/galaxy2.bmp", renderTarget);

		// Game Controller API

		if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) {
			std::cout << "Game Controller Initialization Error: " << SDL_GetError() << std::endl;
			return 3;
		}

		SDL_GameController* controller = nullptr;
		int i;

		for (i = 0; i < SDL_NumJoysticks(); ++i) {
			if (SDL_IsGameController(i)) {
				char* mapping;
				std::cout << "Index '" << i << "' is a compatible controller, named '" <<
					SDL_GameControllerNameForIndex(i) << "'" << std::endl;
				controller = SDL_GameControllerOpen(i);
				//mapping = SDL_GameControllerMapping(controller);
				//std::cout << "Controller " << i << " is mapped as \"" << mapping << std::endl;
				//SDL_free(mapping);
			}
			else {
				std::cout << "Index '" << i << "' is not a compatible controller." << std::endl;
			}
		}

		// -------------------


		// Isto é só para testar que está a funcionar, usar funções!!
		{
			SDL_Texture* droneTexture = nullptr;
			SDL_Surface* droneSurface = SDL_LoadBMP("../graphics/drone.bmp");
			if (droneSurface == NULL)
				std::cout << "Error" << std::endl;
			else
			{
				SDL_SetColorKey(droneSurface, SDL_TRUE, SDL_MapRGB(droneSurface->format, 255, 0, 255));
				droneTexture = SDL_CreateTextureFromSurface(renderTarget, droneSurface);
				if (droneTexture == NULL)
					std::cout << "Error" << std::endl;
			}

			SDL_FreeSurface(droneSurface);

			currentTexture = droneTexture;
		}
		{
			SDL_Texture* backgroundTexture = nullptr;
			SDL_Surface* backgroundSurface = SDL_LoadBMP("../graphics/galaxy2.bmp");
			if (backgroundSurface == NULL)
				std::cout << "Error" << std::endl;
			else
			{
				SDL_SetColorKey(backgroundSurface, SDL_TRUE, SDL_MapRGB(backgroundSurface->format, 255, 0, 255));
				backgroundTexture = SDL_CreateTextureFromSurface(renderTarget, backgroundSurface);
				if (backgroundTexture == NULL)
					std::cout << "Error" << std::endl;
			}

			SDL_FreeSurface(backgroundSurface);

			background = backgroundTexture;
		}

		

		SDL_QueryTexture(currentTexture, NULL, NULL, &textureWidth, &textureHeight);

		frameWidth = textureWidth / 8;
		frameHeight = textureHeight / 2;

		playerRect.x = playerRect.y = 0;
		playerRect.w = frameWidth;
		playerRect.h = frameHeight;

		SDL_SetRenderDrawColor(renderTarget, 0xFF, 0, 0, 0xFF);

		bool isRunning = true;
		SDL_Event ev;

		while (isRunning)
		{
			prevTime = currentTime;
			currentTime = SDL_GetTicks();
			deltaTime = (currentTime - prevTime) / 1000.0f;

			/* Event handling */
			while (SDL_PollEvent(&ev) != 0)
			{
				/* Quit event */
				if (ev.type == SDL_QUIT)
				{
					isRunning = false;
				}
			}
			keyState = SDL_GetKeyboardState(NULL);
			if (keyState[SDL_SCANCODE_RIGHT]) {
				playerPosX += moveSpeed * deltaTime;
				playerPosition.x = playerPosX;
			}
			else if (keyState[SDL_SCANCODE_LEFT]) {
				playerPosX -= moveSpeed * deltaTime;
				playerPosition.x = playerPosX;
			}
			if (keyState[SDL_SCANCODE_DOWN]) {
				playerPosY += moveSpeed * deltaTime;
				playerPosition.y = playerPosY;
			}
			else if (keyState[SDL_SCANCODE_UP]) {
				playerPosY -= moveSpeed * deltaTime;
				playerPosition.y = playerPosY;
			}


			// Game controller movement
			float leftAxisX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
			if (leftAxisX > 4000)
			{
				playerPosition.x += moveSpeed * deltaTime * (leftAxisX / 10000.0f);
			}
			else if (leftAxisX < -4000)
			{
				playerPosition.x += moveSpeed * deltaTime * (leftAxisX / 10000.0f);
			}

			float leftAxisY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
			if (leftAxisY > 4000)
			{
				playerPosition.y += moveSpeed * deltaTime * (leftAxisY / 10000.0f);
			}
			else if (leftAxisY < -4000)
			{
				playerPosition.y += moveSpeed * deltaTime * (leftAxisY / 10000.0f);
			}
			// ------------------------

			frameTime += deltaTime;

			if (frameTime >= 0.1f)
			{
				frameTime = 0;
				playerRect.x += frameWidth;
				if (playerRect.x >= textureWidth) {
					playerRect.x = 0;
					playerRect.y += frameHeight;
					if (playerRect.y >= textureHeight) {
						playerRect.y = 0;
					}
				}
			}

			// Drawing the current image to the window
			SDL_RenderClear(renderTarget);
			SDL_RenderCopy(renderTarget, background, NULL, NULL);
			SDL_RenderCopy(renderTarget, currentTexture, &playerRect, &playerPosition);
			SDL_RenderPresent(renderTarget);

		}

		// Close the game controller
		if (controller != NULL)
			SDL_GameControllerClose(controller);

		SDL_DestroyWindow(window);
		SDL_DestroyTexture(currentTexture);
		SDL_DestroyTexture(background);
		SDL_DestroyRenderer(renderTarget);
		window = nullptr;
		currentTexture = nullptr;
		background = nullptr;
		renderTarget = nullptr;

		SDL_Quit();

		return 0;

}

/*SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error" << std::endl;
	else
	{
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error" << std::endl;
	}

	SDL_FreeSurface(surface);

	return texture;
}*/