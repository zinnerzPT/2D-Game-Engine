#include "Engine.h"
#include <iostream>

#include "SDLWrapper.h"
#include "Window.h"
#include "Texture.h"
#include "Renderer.h"
#include "Pawn.h"

#include "Level.h"

Pawn* player;

Renderer* Engine::renderer = nullptr;
Level* Engine::level = nullptr;

//Level level;

void Engine::init(std::string windowTitle, int windowWidth, int windowHeight)
{
	sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
	window = new Window(windowTitle, windowWidth, windowHeight);
	renderer = new Renderer(window);
	level = new Level();
}

void Engine::start()
{
	const int FPS = 60;
	const float frameDelay = 1000.0f / FPS;
	//int frameTime;

	player = new Pawn("../graphics/drone.bmp", 1, 1);
	Texture* background = new Texture("../graphics/galaxy2.bmp");

	float fixedDeltaTime = 0;

	float desiredFramerate = 60;
	float fixedUpdateDelay = 20;

	desiredFramerate = 1 / desiredFramerate;

	float frameTime = 0;
	int prevTime = 0;
	int currentTime = 0;
	float deltaTime = 0;

	float moveSpeed = 200.0f;
	const Uint8* keyState;

	SDL_GameController* controller = nullptr; // fazer class para game controller?
	int i;

	for (i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {

			std::cout << "Index '" << i << "' is a compatible controller, named '" << SDL_GameControllerNameForIndex(i) << "'" << std::endl;
			controller = SDL_GameControllerOpen(i);

		}
		else {
			std::cout << "Index '" << i << "' is not a compatible controller." << std::endl;
		}
	}

	float playerPosX, playerPosY;
	playerPosX = playerPosY = 0.0f;

	isRunning = true;


	// Game Loop
	while (isRunning)
	{
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;

		//FixedUpdate(physics)

		/*if (frameTime >= 0.1f)
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
		}*/

		/* Event handling */
		HandleEvents();

		/*keyState = SDL_GetKeyboardState(NULL);
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
		}*/

		//frameTime += deltaTime;

		


		//Update();

		player->update(deltaTime);

		renderer->clear();
		//Render level

		renderer->copy(background, NULL, NULL);
		//renderer->copy(currentTexture, &playerRect, &playerPosition);
		player->render();

		renderer->present();

		window->updateSurface();

		//Fixed framerate
		if (frameDelay > deltaTime) {
			SDL_Delay(frameDelay - deltaTime);
		}
	}

	// Close the game controller
	if (controller != NULL)
		SDL_GameControllerClose(controller);
}

void Engine::HandleEvents()
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev) != 0)
	{
		switch (ev.type) {
		/* Quit event */
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
		}
	}
}

Engine::~Engine()
{
	delete renderer;
	delete window;
	delete sdl;
	delete level;
}
