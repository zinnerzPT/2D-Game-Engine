#pragma once

#include <SDL2/SDL.h>
#include <string>

class Window
{
public:
	Window(std::string title, int windowWidth, int windowHeight);

	SDL_Surface* getSurface();
	SDL_Window* getWindow() { return window; }

	void updateSurface();

	~Window();
private:
	SDL_Window* window;
};

