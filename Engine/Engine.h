#pragma once

#include <string>

class Engine
{

private:
	Engine() {};

public:

	void init(std::string windowTitle, int windowWidth, int windowHeight, class Level* gameLevel);
	void start();

	inline static class Level* getLevel() { return level; };
	inline class SceneViewer* getSceneViewer() { return viewer; };
	static Engine* getInstance();

	~Engine();
private:
	bool isRunning;
	class SDLWrapper* sdl = nullptr;
	static class Level* level;
	class SceneViewer* viewer;

	static Engine* instance;
};

