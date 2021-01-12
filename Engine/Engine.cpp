#include "Engine.h"

#include "SDLWrapper.h"
#include "Window.h"
#include "Renderer.h"
#include "Pawn.h"
#include "Level.h"
#include "SceneViewer.h"
#include <box2d/box2d.h>

#include "Input.h"

Engine* Engine::instance = nullptr;

//Renderer* Engine::renderer = nullptr;
Level* Engine::level = nullptr;

void Engine::init(std::string windowTitle, int windowWidth, int windowHeight)
{
	sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
	viewer = new SceneViewer(windowTitle, windowWidth, windowHeight);
	//renderer = new Renderer(viewer->getWindow());
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
		isRunning = Input::getInstance()->handleInput();

		//Update();
		level->update(deltaTime);

		viewer->clear();
		//renderer->clear();
		//Render level

		frameTime += deltaTime;
		if (frameTime >= 0.1f)
		{
			frameTime = 0;
			level->animate();
		}

		level->render(viewer);

		viewer->swapBuffers();

		//renderer->present();

		//viewer->getWindow()->updateSurface();

		//Actors to add/remove
		level->updateActors();

		//Animations to add/remove
		level->updateAnimations();

		//Update enabled/disabled status
		level->updateBodies();

		//Fixed framerate
		if (frameDelay > deltaTime) {
			SDL_Delay(frameDelay - deltaTime);
		}
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
	//delete renderer;
	delete viewer;
	delete sdl;
	delete level;
}
