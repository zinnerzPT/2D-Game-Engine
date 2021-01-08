#include "Input.h"
#include <SDL2/SDL.h>

#include <vector>
#include "Engine.h"

Input* Input::instance = nullptr;

struct Key {
	const std::string keyName;
	const SDL_Scancode scancode;
	bool isKeyDown = false;
	bool isKey = false;
	bool isKeyUp = false;

	//Key(std::string name, SDL_Scancode code) : keyName(name), scancode(code) {}
};

//List of Keys
Key right{ "Right", SDL_SCANCODE_RIGHT };
Key left{ "Left", SDL_SCANCODE_LEFT };

std::vector<Key*> keys = {
	&right, &left
};

//Keys to release
std::vector<Key> keysUp;

Input* Input::getInstance()
{
	if (instance == nullptr) {
		instance = new Input();
	}
	return instance;
}

bool Input::handleInput() {
	// releases the key released on the previous frame
	for (Key k : keysUp) {
		k.isKeyUp = false;
		//std::cout << k.keyName << " cleared." << std::endl;
	}

	keysUp.clear();

	SDL_Event ev;
	while (SDL_PollEvent(&ev) != 0)
	{
		switch (ev.type) {
			/* Quit event */

		case SDL_QUIT:
			return false;
			break;

		case SDL_KEYDOWN:
			handleKeyDown(ev.key.keysym, ev.key.repeat);
			break;

		case SDL_KEYUP:
			handleKeyUp(ev.key.keysym, ev.key.repeat);
			break;

		default:
			//std::cout << "something happened but I don't know what" << std::endl;
			break;
		}
	}
	return true;
}

void Input::handleKeyDown(SDL_Keysym keyDown, int repeat)
{
	for (Key* key : keys)
	{
		if (key->scancode == keyDown.scancode)
		{
			if (repeat == 0) {
				key->isKeyDown = true;
				//std::cout << key->keyName << " pressed." << std::endl;
			}
			else {
				key->isKeyDown = false;
			}
			key->isKey = true;
			return;
		}
	}
}

void Input::handleKeyUp(SDL_Keysym keyUp, int repeat)
{

	for (Key* key : keys)
	{
		if (key->scancode == keyUp.scancode)
		{
			key->isKey = false;
			key->isKeyUp = true;
			keysUp.push_back(*key);
			//std::cout << key->keyName << " released." << std::endl;
			return;
		}
	}
}


bool Input::getKey(std::string keyName) {
	for (Key* k : keys) {
		if (k->keyName == keyName)
			return k->isKey;
	}
	return false;
}

bool Input::getKeyDown(std::string keyName) {
	for (Key* k : keys) {
		if (k->keyName == keyName)
			return k->isKeyDown;
	}
	return false;
}

bool Input::getKeyUp(std::string keyName) {
	for (Key* k : keys) {
		if (k->keyName == keyName)
			return k->isKeyUp;
	}
	return false;
}
