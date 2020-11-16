#pragma once

#include <string>

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

	~Engine();
private:
	bool isRunning;
	class SDLWrapper* sdl;
	class Window* window;

public:
	static class Renderer* renderer;
	
};

