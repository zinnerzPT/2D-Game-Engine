#pragma once

#include <string>

#include "Level.h"

class Engine
{
public:

	void init(std::string windowTitle, int windowWidth, int windowHeight);
	void start();

	void HandleEvents();
	//update
	//render
	//clean
	//bool running() { return isRunning; }

	static Level* getLevel();

	~Engine();
private:
	bool isRunning;
	class SDLWrapper* sdl;
	class Window* window;
	static Level* level;

public:
	static class Renderer* renderer;
	
};

