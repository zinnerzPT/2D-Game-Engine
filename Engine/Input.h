#pragma once
#include <string>

class Input
{
private:
	Input() {};
	void init();

	void handleKeyDown(struct SDL_Keysym key, int repeat);
	void handleKeyUp(struct SDL_Keysym key, int repeat);

public:
	static Input* getInstance();

	bool handleInput();

	// Return true if the key is pressed
	bool getKey(std::string keyName);

	// Return true if the key was pressed this frame
	bool getKeyDown(std::string keyName);

	// Return true if the key was released this frame
	bool getKeyUp(std::string keyName);
private:
	static Input* instance;
};

