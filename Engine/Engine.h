#pragma once

#include <string>

class Engine
{

private:
	Engine() {};

public:

	void init(std::string windowTitle, int windowWidth, int windowHeight);
	void start();

	void HandleEvents();

	static class Level* getLevel() { return level; };
	static Engine* getInstance();

	~Engine();
private:
	bool isRunning;
	class SDLWrapper* sdl;
	class SceneViewer* viewer;
	static class Level* level;

	static Engine* instance;

public:
//	static class Renderer* renderer;

};

