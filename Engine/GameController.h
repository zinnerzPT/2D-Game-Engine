#pragma once
#include <string>

class GameController
{
public:
	GameController(int id);

	float getLeftXAxis();
	float getLeftYAxis();

	float getRightXAxis();
	float getRightYAxis();

	float getLeftTriggerAxis();
	float getRightTriggerAxis();

	//bool getButtonA();

	// Return true if the button is pressed
	bool getButton(std::string buttonName);

	// Return true if the button was pressed this frame
	bool getButtonDown(std::string buttonName);

	// Return true if the button was released this frame
	bool getButtonUp(std::string buttonName);

	void handleButtonDown(uint8_t button);
	void handleButtonUp(uint8_t button);
	
	void releaseButtons();

	inline int getId() { return id; };

	~GameController();

private:
	int id;
};

