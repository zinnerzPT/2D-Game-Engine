#include "Input.h"
#include <SDL2/SDL.h>

#include <vector>
#include "Engine.h"

Input* Input::instance = nullptr;

struct Key {
	const std::string keyName;
	const SDL_Keycode keycode;
	bool isKeyDown = false;
	bool isKey = false;
	bool isKeyUp = false;

	//Key(std::string name, SDL_Keycode code) : keyName(name), keycode(code) {}
};

//List of Keys
#pragma region KeyList
// Letters
Key letterA{ "A", SDLK_a };
Key letterB{ "B", SDLK_b };
Key letterC{ "C", SDLK_c };
Key letterD{ "D", SDLK_d };
Key letterE{ "E", SDLK_e };
Key letterF{ "F", SDLK_f };
Key letterG{ "G", SDLK_g };
Key letterH{ "H", SDLK_h };
Key letterI{ "I", SDLK_i };
Key letterJ{ "J", SDLK_j };
Key letterK{ "K", SDLK_k };
Key letterL{ "L", SDLK_l };
Key letterM{ "M", SDLK_m };
Key letterN{ "N", SDLK_n };
Key letterO{ "O", SDLK_o };
Key letterP{ "P", SDLK_p };
Key letterQ{ "Q", SDLK_q };
Key letterR{ "R", SDLK_r };
Key letterS{ "S", SDLK_s };
Key letterT{ "T", SDLK_t };
Key letterU{ "U", SDLK_u };
Key letterV{ "V", SDLK_v };
Key letterW{ "W", SDLK_w };
Key letterX{ "X", SDLK_x };
Key letterY{ "Y", SDLK_y };
Key letterZ{ "Z", SDLK_z };

// Numbers
Key number1{ "1", SDLK_1 };
Key number2{ "2", SDLK_2 };
Key number3{ "3", SDLK_3 };
Key number4{ "4", SDLK_4 };
Key number5{ "5", SDLK_5 };
Key number6{ "6", SDLK_6 };
Key number7{ "7", SDLK_7 };
Key number8{ "8", SDLK_8 };
Key number9{ "9", SDLK_9 };
Key number0{ "0", SDLK_0 };

// Arrows
Key arrowUp{ "Up", SDLK_UP };
Key arrowDown{ "Down", SDLK_DOWN };
Key arrowLeft{ "Left", SDLK_LEFT };
Key arrowRight{ "Right", SDLK_RIGHT };

// Other Keys
Key leftShift{ "Left Shift", SDLK_LSHIFT };
Key rightShift{ "Right Shift", SDLK_RSHIFT };
Key leftCtrl{ "Left Ctrl", SDLK_LCTRL };
Key rightCtrl{ "Right Ctrl", SDLK_RCTRL };
Key leftAlt{ "Left Alt", SDLK_LALT };
Key rightAlt{ "Right Alt", SDLK_RALT };
Key space{ "Space", SDLK_SPACE };
Key tab{ "Tab", SDLK_TAB };
Key capsLock{ "Caps Lock", SDLK_CAPSLOCK };
Key returnKey{ "Return", SDLK_RETURN };
Key backspace{ "Backspace", SDLK_BACKSPACE };

// Function Keys

std::vector<Key*> keys = {
	// Letters
	&letterA, &letterB, &letterC, &letterD, &letterE, &letterF, &letterG, &letterH, &letterI, &letterJ, &letterK, &letterL, &letterM, &letterN, &letterO, &letterP, &letterQ, &letterR, &letterS, &letterT, &letterU, &letterV, &letterW, &letterX, &letterY, &letterZ,

	// Numbers
	&number1, &number2, &number3, &number4, &number5, &number6, &number7, &number8, &number9, &number0,

	// Arrows
	&arrowUp, &arrowDown, &arrowLeft, &arrowRight,

	// Other Keys
	&leftShift, &rightShift, &leftCtrl, &rightCtrl, &leftAlt, &rightAlt, &space, &tab, &capsLock, &returnKey, &backspace
};
#pragma endregion

//Keys to release
std::vector<Key*> keysUp;
std::vector<Key*> keysDown;

Input* Input::getInstance()
{
	if (instance == nullptr) {
		instance = new Input();
	}
	return instance;
}

bool Input::handleInput() {
	// releases the key released on the previous frame
	for (Key *k : keysUp) {
		k->isKeyUp = false;
		//std::cout << k.keyName << " cleared." << std::endl;
	}

	for (Key* k : keysDown) {
		k->isKeyDown = false;
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
		if (key->keycode == keyDown.sym)
		{
			if (repeat == 0) {
				key->isKeyDown = true;
				keysDown.push_back(key);
				//std::cout << key->keyName << " pressed." << std::endl;
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
		if (key->keycode == keyUp.sym)
		{
			key->isKey = false;
			key->isKeyUp = true;
			keysUp.push_back(key);
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
