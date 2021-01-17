#include "GameController.h"
#include <SDL2/SDL_gamecontroller.h>
#include <vector>

//FOR DEBUG PURPOSES ONLY
#include <iostream>

#define MAX_AXIS 32767.0f

struct Button {
	const std::string buttonName;
	const SDL_GameControllerButton buttonCode;
	bool isButtonDown = false;
	bool isButton = false;
	bool isButtonUp = false;
};

//List of Buttons
#pragma region ButtonList
Button aButton{ "A", SDL_CONTROLLER_BUTTON_A };
Button bButton{ "B", SDL_CONTROLLER_BUTTON_B };
Button xButton{ "X", SDL_CONTROLLER_BUTTON_X };
Button yButton{ "Y", SDL_CONTROLLER_BUTTON_Y };
Button backButton{ "Back", SDL_CONTROLLER_BUTTON_BACK };
Button guideButton{ "Guide", SDL_CONTROLLER_BUTTON_GUIDE };
Button startButton{ "Start", SDL_CONTROLLER_BUTTON_START };
Button leftStickButton{ "Left Stick",SDL_CONTROLLER_BUTTON_LEFTSTICK };
Button rightStickButton{ "Right Stick", SDL_CONTROLLER_BUTTON_RIGHTSTICK };
Button leftShoulderButton{ "Left Shoulder",SDL_CONTROLLER_BUTTON_LEFTSHOULDER };
Button rightShoulderButton{ "Right Shoulder",SDL_CONTROLLER_BUTTON_RIGHTSHOULDER };
Button dpadUpButton{ "Up",SDL_CONTROLLER_BUTTON_DPAD_UP };
Button dpadDownButton{ "Down",SDL_CONTROLLER_BUTTON_DPAD_DOWN };
Button dpadLeftButton{ "Left",SDL_CONTROLLER_BUTTON_DPAD_LEFT };
Button dpadRightButton{ "Right",SDL_CONTROLLER_BUTTON_DPAD_RIGHT };

std::vector<Button*> buttons = {
	&aButton,
	&bButton,
	&xButton,
	&yButton,
	&backButton,
	&guideButton,
	&startButton,
	&leftStickButton,
	&rightStickButton,
	&leftShoulderButton,
	&rightShoulderButton,
	&dpadUpButton,
	&dpadDownButton,
	&dpadLeftButton,
	&dpadRightButton
};
#pragma endregion

//Buttons to release
std::vector<Button*> buttonsUp;
std::vector<Button*> buttonsDown;

SDL_GameController* controller;

GameController::GameController(int id)
{
	this->id = id;
	controller = SDL_GameControllerOpen(id);
}

void GameController::handleButtonDown(uint8_t button)
{
	for (Button* b : buttons)
	{
		if ((uint8_t)b->buttonCode == button)
		{
			b->isButtonDown = true;
			buttonsDown.push_back(b);

			b->isButton = true;
			return;
		}
	}
}

void GameController::handleButtonUp(uint8_t button)
{
	for (Button* b : buttons)
	{
		if ((uint8_t)b->buttonCode == button)
		{
			b->isButton = false;
			b->isButtonUp = true;
			buttonsUp.push_back(b);
			return;
		}
	}
}

// Handles button presses on previous frames
void GameController::releaseButtons() {
	// releases the button released on the previous frame
	for (Button* b : buttonsUp) {
		b->isButtonUp = false;
	}

	for (Button* b : buttonsDown) {
		b->isButtonDown = false;
	}
}

// Game controller Axis
float GameController::getLeftXAxis()
{
	return SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) / MAX_AXIS;
}

float GameController::getLeftYAxis()
{
	return SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) / MAX_AXIS;
}

float GameController::getRightXAxis()
{
	return SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX) / MAX_AXIS;
}

float GameController::getRightYAxis()
{
	return SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY) / MAX_AXIS;
}

float GameController::getLeftTriggerAxis()
{
	return SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT) / MAX_AXIS;
}

float GameController::getRightTriggerAxis()
{
	return SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) / MAX_AXIS;
}

bool GameController::getButton(std::string buttonName) {
	for (Button* b : buttons) {
		if (b->buttonName == buttonName)
			return b->isButton;
	}
	return false;
}

bool GameController::getButtonDown(std::string buttonName) {
	for (Button* b : buttons) {
		if (b->buttonName == buttonName)
			return b->isButtonDown;
	}
	return false;
}

bool GameController::getButtonUp(std::string buttonName) {
	for (Button* b : buttons) {
		if (b->buttonName == buttonName)
			return b->isButtonUp;
	}
	return false;
}




GameController::~GameController()
{
	SDL_GameControllerClose(controller);
}