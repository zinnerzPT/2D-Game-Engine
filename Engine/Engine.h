#pragma once

#include <string>
#include <thread>

class Engine
{

private:
	Engine() {};

	void physicsUpdate();

public:

	void init(std::string windowTitle, int windowWidth, int windowHeight, class Level* gameLevel);
	void start();

	//void HandleEvents();

	static class Level* getLevel() { return level; };
	static Engine* getInstance();

	~Engine();
private:
	bool isRunning;
	class SDLWrapper* sdl = nullptr;
	class Window* window = nullptr;
	static class Level* level;

	std::thread physicsThread;

	static Engine* instance;

public:
	static class Renderer* renderer;

};

