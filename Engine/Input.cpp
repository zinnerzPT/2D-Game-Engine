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
Key f1{ "F1", SDLK_F1 };
Key f2{ "F2", SDLK_F2 };
Key f3{ "F3", SDLK_F3 };
Key f4{ "F4", SDLK_F4 };
Key f5{ "F5", SDLK_F5 };
Key f6{ "F6", SDLK_F6 };
Key f7{ "F7", SDLK_F7 };
Key f8{ "F8", SDLK_F8 };
Key f9{ "F9", SDLK_F9 };
Key f10{ "F10", SDLK_F10 };
Key f11{ "F11", SDLK_F11 };
Key f12{ "F12", SDLK_F12 };
Key f13{ "F13", SDLK_F13 };
Key f14{ "F14", SDLK_F14 };
Key f15{ "F15", SDLK_F15 };
Key f16{ "F16", SDLK_F16 };
Key f17{ "F17", SDLK_F17 };
Key f18{ "F18", SDLK_F18 };
Key f19{ "F19", SDLK_F19 };
Key f20{ "F20", SDLK_F20 };
Key f21{ "F21", SDLK_F21 };
Key f22{ "F22", SDLK_F22 };
Key f23{ "F23", SDLK_F23 };
Key f24{ "F24", SDLK_F24 };

std::vector<Key*> keys = {
	// Letters
	&letterA, &letterB, &letterC, &letterD, &letterE, &letterF, &letterG, &letterH, &letterI, &letterJ, &letterK, &letterL, &letterM, &letterN, &letterO, &letterP, &letterQ, &letterR, &letterS, &letterT, &letterU, &letterV, &letterW, &letterX, &letterY, &letterZ,

	// Numbers
	&number1, &number2, &number3, &number4, &number5, &number6, &number7, &number8, &number9, &number0,

	// Arrows
	&arrowUp, &arrowDown, &arrowLeft, &arrowRight,

	// Other Keys
	&leftShift, &rightShift, &leftCtrl, &rightCtrl, &leftAlt, &rightAlt, &space, &tab, &capsLock, &returnKey, &backspace,

	// Function keys
	&f1, &f2, &f3, &f4, &f5, &f6, &f7, &f8, &f9, &f10, &f11, &f12, &f13, &f14, &f15, &f16, &f17, &f18, &f19, &f20, &f21, &f22, &f23, &f24
};
#pragma endregion

//Keys to release
std::vector<Key*> keysUp;
std::vector<Key*> keysDown;

Input::Input() {

	// Initialize controllers
	for (int i = 0; i < SDL_NumJoysticks(); ++i)
	{
		if (SDL_IsGameController(i))
		{
			addController(i);
			//std::cout << "Index '" << i << "' is a compatible controller, named '" << SDL_GameControllerNameForIndex(i) << "'" << std::endl;
		}
		else
		{
			//std::cout << "Index '" << i << "' is not a compatible controller." << std::endl;
		}
	}
}

Input::~Input() {
	for (GameController* c : controllers) {
		this->controllers.erase(std::remove(this->controllers.begin(), this->controllers.end(), c), this->controllers.end());
		delete c;
	}
}

Input* Input::getInstance()
{
	if (instance == nullptr) {
		instance = new Input();
	}
	return instance;
}

bool Input::handleInput() {
	// releases the key released on the previous frame
	for (Key* k : keysUp) {
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

		case SDL_CONTROLLERDEVICEADDED:
			addController(ev.cdevice.which);
			break;

		case SDL_CONTROLLERDEVICEREMOVED:
			removeController(ev.cdevice.which);
			break;

		case SDL_CONTROLLERBUTTONDOWN:
			getControllerWithId(ev.cbutton.which)->handleButtonDown(ev.cbutton.button);				
			break;

		case SDL_CONTROLLERBUTTONUP:
			getControllerWithId(ev.cbutton.which)->handleButtonUp(ev.cbutton.button);
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

void Input::addController(int id)
{
	controllers.push_back(new GameController(id));
}

void Input::removeController(int id)
{
	for (GameController* c : controllers) {
		if (c->getId() == id) {
			this->controllers.erase(std::remove(this->controllers.begin(), this->controllers.end(), c), this->controllers.end());
			delete c;
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

GameController* Input::getController(int i) {
	if (controllers.size() > 0)
		return controllers[i];
	return NULL;
}

GameController* Input::getControllerWithId(int id) {
	if (controllers.size() > 0) {
		for (GameController* c : controllers) {
			if (c->getId() == id)
				return c;
		}
	}
	return NULL;
}
