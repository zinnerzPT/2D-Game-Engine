#include "Input.h"
#include <SDL2/SDL.h>

#include <iostream>
#include <vector>
#include "Engine.h"

Input* Input::instance = nullptr;

struct Key {
	std::string keyName;
	bool isKeyDown;
	bool isKey;
	bool isKeyUp;

	Key(std::string name) : keyName(name), isKeyDown(false), isKey(false), isKeyUp(false) { }
};

struct Axis {
	Key key;
	float axis;
};

//List of Keys
std::vector<Key*> keys;
Key right("Right");
Key left("Left");

std::vector<Key> keysUp;

Input* Input::getInstance()
{
	if (instance == nullptr) {
		instance = new Input();
		instance->init();
	}
	return instance;
}

void Input::init() {
	// Init each key by adding them to vector keys
	keys.push_back(&right);
	keys.push_back(&left);
}

bool Input::handleInput() {
	for (Key k : keysUp) {
		k.isKeyUp = false;
	}

	keysUp.clear();

	const Uint8* keyState;

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
			//std::cout << "some key was pressed but idk which one" << std::endl;
			break;
		}
	}
	return true;
}

void Input::handleKeyDown(SDL_Keysym key, int repeat)
{
	switch (key.scancode) {
	case SDL_SCANCODE_RIGHT:
		if (repeat == 0) {
			right.isKeyDown = true;
			std::cout << "Right" << std::endl;
		}
		else {
			right.isKeyDown = false;
		}
		right.isKey = true;

		break;

	case SDL_SCANCODE_LEFT:
		if (repeat == 0) {
			left.isKeyDown = true;
			std::cout << "Left" << std::endl;
		}
		else {
			left.isKeyDown = false;
		}
		left.isKey = true;
		break;
	}
}

void Input::handleKeyUp(SDL_Keysym key, int repeat)
{
	switch (key.scancode) {
	case SDL_SCANCODE_RIGHT:
		right.isKey = false;
		right.isKeyUp = true;
		keysUp.push_back(right);
		break;

	case SDL_SCANCODE_LEFT:
		left.isKey = false;
		left.isKeyUp = true;
		keysUp.push_back(left);
		break;
	}
}


bool Input::getKey(std::string keyName) {
	for (Key *k : keys) {
		if (k->keyName == keyName)
			return k->isKey;
	}
	return false;
}

bool Input::getKeyDown(std::string keyName) {
	for (Key *k : keys) {
		if (k->keyName == keyName)
			return k->isKeyDown;
	}
	return false;
}

bool Input::getKeyUp(std::string keyName) {
	for (Key *k : keys) {
		if (k->keyName == keyName)
			return k->isKeyUp;
	}
	return false;
}
