#include "Engine.h"

#include "SDLWrapper.h"
#include "Pawn.h"
#include "Level.h"
#include "SceneViewer.h"
#include <box2d/box2d.h>

#include "Input.h"

Engine* Engine::instance = nullptr;

Level* Engine::level = nullptr;

void Engine::init(std::string windowTitle, int windowWidth, int windowHeight, Level* gameLevel)
{
	sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
	// OpenGL initialization
	viewer = new SceneViewer(windowTitle, windowWidth, windowHeight);

	// Old SDL way
	//window = new Window(windowTitle, windowWidth, windowHeight);
	//renderer = new Renderer(window);

	level = gameLevel;
}

void Engine::start()
{
	float frameTime = 0;
	int prevTime = 0;
	int currentTime = 0;
	float deltaTime = 0;

	int velocityIterations = 6;
	int positionIterations = 2;

	isRunning = true;

	// Game Loop
	while (isRunning)
	{
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;

		//Update the physics
		level->getWorld()->Step(deltaTime, velocityIterations, positionIterations);

		/* Event handling */
		isRunning = Input::getInstance()->handleInput();

		//Update();
		level->update(deltaTime);

		// Old SDL way
		//renderer->clear();
		//Render level

		viewer->clear();

		frameTime += deltaTime;
		if (frameTime >= 0.1f)
		{
			frameTime = 0;
			level->animate();
		}

		// Old SDL way
		//level->render();
		//renderer->present();

		level->draw(viewer);
		viewer->swapBuffers();

		//Actors to add/remove
		level->updateActors();

		//Animations to add/remove
		level->updateAnimations();

		//UICanvases to add/remove
		level->updateCanvases();

		//Update enabled/disabled status
		level->updateBodies();
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
	delete viewer;
	delete sdl;
	delete level;
}
