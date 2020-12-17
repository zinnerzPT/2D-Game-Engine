#include "Input.h"
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "Engine.h"

Input* Input::instance = nullptr;

enum Key
{

};

struct Button {
	Key key;
	bool isButtonDown;
	bool isButton;
	bool isButtonUp;
};

struct Axis {
	Key key;
	float axis;
};


Input* Input::getInstance()
{
	if (instance == nullptr) {
		instance = new Input();
	}
	return instance;
}

bool Input::handleInput(){
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

	/*keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_RIGHT]) {
		
		//moveRight(moveSpeed * deltaTime);
	}
	else if (keyState[SDL_SCANCODE_LEFT]) {
		//moveRight(-moveSpeed * deltaTime);
	}
	if (keyState[SDL_SCANCODE_DOWN]) {
		//moveUp(-moveSpeed * deltaTime);
	}
	else if (keyState[SDL_SCANCODE_UP]) {
		//moveUp(moveSpeed * deltaTime);
	}

	// Game controller movement
	//float leftAxisX = controller->getXAxis();
	//if (leftAxisX > 0.3f || leftAxisX < -0.3f)
	{
		//moveRight(moveSpeed * deltaTime * leftAxisX);
	}

	//float leftAxisY = controller->getYAxis();
	//if (leftAxisY > 0.3f || leftAxisY < -0.3f)
	{
		//moveUp(moveSpeed * deltaTime * -leftAxisY);
	}*/

}

void Input::handleKeyDown(SDL_Keysym key, int repeat)
{
	switch (key.scancode) {
	case SDL_SCANCODE_RIGHT:
		if(repeat == 0)
			std::cout << "Right Pressed" << std::endl;
		break;

	case SDL_SCANCODE_LEFT:
		if (repeat == 0)
		std::cout << "Left Pressed" << std::endl;
		break;
	}
}

void Input::handleKeyUp(SDL_Keysym key, int repeat)
{
	switch (key.scancode) {
	case SDL_SCANCODE_RIGHT:
		if (repeat == 0)
			std::cout << "Right Released" << std::endl;
		break;

	case SDL_SCANCODE_LEFT:
		if (repeat == 0)
			std::cout << "Left Released" << std::endl;
		break;
	}
}
