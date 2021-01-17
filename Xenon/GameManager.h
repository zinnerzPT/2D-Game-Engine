#pragma once

#include "Actor.h"

class GameManager : public Actor
{
private:
	GameManager() {};

public:
	void update(float deltaTime) override;

	void addScore(int points);
	int getScore() { return score; };
	int getHiScore() { return hiScore; };

	void spawnPlayer(int x, int y);
	float getHealth();
	int getLives() { return playerLives; };

	void loseLife(int i = 1);
	void addLife(int i = 1);

	~GameManager();

	static GameManager* getInstance();

	static void clearInstance();

private:
	int score = 0;
	int hiScore = 5000;

	int playerLives = 4;

	class Spaceship* ship;

	bool canRespawn;
	float timeSinceDeath = 0;

	static GameManager* instance;

public:

};
