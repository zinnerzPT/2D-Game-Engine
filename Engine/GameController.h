#pragma once

class GameController
{
public:
	GameController();

	inline bool getIsDetected() { return isDetected; };
	float getXAxis();
	float getYAxis();
	bool getButtonA();

	~GameController();

private:
	bool isDetected = false;
};

