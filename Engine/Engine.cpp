#include "Engine.h"

#include "SDLWrapper.h"
#include "Window.h"
#include "Renderer.h"
#include "Pawn.h"
#include "Level.h"
#include <box2d/box2d.h>
#include <thread>

#include "Input.h"

#define PHYSICS_TICKS_PER_SECOND 60.0f

Engine* Engine::instance = nullptr;

Renderer* Engine::renderer = nullptr;
Level* Engine::level = nullptr;

void Engine::init(std::string windowTitle, int windowWidth, int windowHeight, Level* gameLevel)
{
	sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
	window = new Window(windowTitle, windowWidth, windowHeight);
	renderer = new Renderer(window);
	level = gameLevel;
}

void Engine::start()
{
	//const int FPS = 60;
	//const float frameDelay = 1000.0f / FPS;
	//int frameTime;

	float frameTime = 0;
	int prevTime = 0;
	int currentTime = 0;
	float deltaTime = 0;

	isRunning = true;

	// Physics variables

	physicsThread = std::thread{ &Engine::physicsUpdate, this };

	// Game Loop
	while (isRunning)
	{
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;

		/* Event handling */
		isRunning = Input::getInstance()->handleInput();

		//Update();
		level->update(deltaTime);

		renderer->clear();
		//Render level

		frameTime += deltaTime;
		if (frameTime >= 0.1f)
		{
			frameTime = 0;
			level->animate();
		}

		level->render();

		renderer->present();

		window->updateSurface();

		//Actors to add/remove
		level->updateActors();

		//Animations to add/remove
		level->updateAnimations();

		//Update enabled/disabled status
		level->updateBodies();

		//Fixed framerate
		//if (frameDelay > deltaTime) {
		//	SDL_Delay(frameDelay - deltaTime);
		//}
	}

	physicsThread.join();
}

void Engine::physicsUpdate()
{
	long timeStep = 1000.0f / PHYSICS_TICKS_PER_SECOND;
	int velocityIterations = 6;
	int positionIterations = 2;

	while (isRunning) {
		//Update the physics
		level->getWorld()->Step(timeStep / 1000.0f, velocityIterations, positionIterations);
		//std::cout << timeStep << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds{ timeStep });
	}
}

Engine* Engine::getInstance()
{
	if (instance == nullptr) {
		instance = new Engine();
	}
	return instance;
}

Engine::~Engine()
{
	delete renderer;
	delete window;
	delete sdl;
	delete level;
}


