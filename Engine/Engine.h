#pragma once

#include <string>

class Engine
{
public:

	void init(std::string windowTitle, int windowWidth, int windowHeight);
	void start();

	void HandleEvents();

	static class Level* getLevel() { return level; };

	~Engine();
private:
	bool isRunning;
	class SDLWrapper* sdl;
	class Window* window;
	static class Level* level;

public:
	static class Renderer* renderer;

};

