#pragma once
class Input
{
private:
	Input() {};

public:

	static Input* getInstance();

	bool handleInput();

	void handleKeyDown(struct SDL_Keysym key, int repeat);
	void handleKeyUp(struct SDL_Keysym key, int repeat);
private:
	static Input* instance;
};

