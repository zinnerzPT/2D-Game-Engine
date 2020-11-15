#pragma once

#include <string>

class Engine
{
private:
	int RunLogics(); // VERY PLACEHOLDER
	//SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget);
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
	class Renderer* renderer;
};

