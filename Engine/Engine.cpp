#include "Engine.h"
#include <iostream>

#include "SDLWrapper.h"
#include "Window.h"
#include "Texture.h"
#include "Renderer.h"

#include "Level.h"


//Level level;

void Engine::init(std::string windowTitle, int windowWidth, int windowHeight)
{
	sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
	window = new Window(windowTitle, windowWidth, windowHeight);
	renderer = new Renderer(window);
}

void Engine::start()
{
	Texture* currentTexture = new Texture("../graphics/drone.bmp", renderer);
	Texture* background = new Texture("../graphics/galaxy2.bmp", renderer);

	//float frameTime = 0;
	//int prevTime = 0;
	//int currentTime = 0;
	//float deltaTime = 0;
	float fixedDeltaTime = 0;

	float desiredFramerate = 60;
	float fixedUpdateDelay = 20;

	desiredFramerate = 1 / desiredFramerate;

	SDL_Rect playerRect;
	SDL_Rect playerPosition;
	playerPosition.x = playerPosition.y = 0;
	playerPosition.w = playerPosition.h = 32;
	int frameWidth, frameHeight;
	int textureWidth, textureHeight;
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

	currentTexture->query(&textureWidth, &textureHeight);

	frameWidth = textureWidth / 8;
	frameHeight = textureHeight / 2;

	playerRect.x = playerRect.y = 0;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;


	float playerPosX, playerPosY;
	playerPosX = playerPosY = 0.0f;

	bool isRunning = true;
	SDL_Event ev;

	// Game Loop
	while (isRunning)
	{
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;

		//FixedUpdate(physics)
		/*while(deltaTime < desiredFramerate){ //deltaTime < a single frame

			//FixedUpdate() (physics)

			//OnTriggerXXX()
			//OnCollisionXXX()

			currentTime = SDL_GetTicks();
			deltaTime = (currentTime - prevTime) / 1000.0f;
			if (deltaTime < desiredFramerate) {
				SDL_Delay(fixedUpdateDelay-fixedDeltaTime);
			}
			std::cout << fixedDeltaTime << std::endl;
			//wait for next FixedUpdate

		}*/

		/* Event handling */
		while (SDL_PollEvent(&ev) != 0)
		{
			/* Quit event */
			if (ev.type == SDL_QUIT)
				isRunning = false;
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



		//Update();


		//Render level
		renderer->clear();
		renderer->copy(background, NULL, NULL);
		renderer->copy(currentTexture, &playerRect, &playerPosition);
		renderer->present();

		window->updateSurface();
	}

	// Close the game controller
	if (controller != NULL)
		SDL_GameControllerClose(controller);
}

Engine::~Engine()
{
	delete renderer;
	delete window;
	delete sdl;
}
