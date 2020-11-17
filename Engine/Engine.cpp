#include "Engine.h"

#include "SDLWrapper.h"
#include "Window.h"
#include "Renderer.h"
#include "Pawn.h"

#include "Level.h"
#include <box2d/box2d.h>

Renderer* Engine::renderer = nullptr;
Level* Engine::level = nullptr;

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


	float frameTime = 0;
	int prevTime = 0;
	int currentTime = 0;
	float deltaTime = 0;

	isRunning = true;

	// Physics variables
	float timeStep = 1.0f / 60.0f;
	int velocityIterations = 6;
	int positionIterations = 2;

	// Game Loop
	while (isRunning)
	{
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;

		//Update the physics
		level->getWorld()->Step(timeStep, velocityIterations, positionIterations);

		/* Event handling */
		HandleEvents();


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

		//Fixed framerate
		if (frameDelay > deltaTime) {
			SDL_Delay(frameDelay - deltaTime);
		}
	}
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
