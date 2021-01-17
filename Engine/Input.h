#pragma once
#include <string>
#include <vector>
#include "GameController.h"

class Input
{
private:
	Input();

	void handleKeyDown(struct SDL_Keysym key, int repeat);
	void handleKeyUp(struct SDL_Keysym key, int repeat);

	void addController(int id);
	void removeController(int id);

public:
	static Input* getInstance();
	~Input();

	bool handleInput();

	// Return true if the key is pressed
	bool getKey(std::string keyName);

	// Return true if the key was pressed this frame
	bool getKeyDown(std::string keyName);

	// Return true if the key was released this frame
	bool getKeyUp(std::string keyName);

	GameController* getController(int i);
	GameController* getControllerWithId(int id);
private:
	static Input* instance;

	std::vector<GameController*> controllers;
};

