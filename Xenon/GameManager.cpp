#include "GameManager.h"
#include "Spaceship.h"

#define DEATH_COOLDOWN 2.0f

GameManager* GameManager::instance = nullptr;

GameManager::~GameManager()
{
	instance = nullptr;	
}

GameManager* GameManager::getInstance()
{
	if (instance == nullptr) {
		instance = new GameManager();
	}
	return instance;
}

void GameManager::update(float deltaTime)
{
	if (canRespawn) {
		if (timeSinceDeath > DEATH_COOLDOWN) {
			spawnPlayer(304, 80);
		}
		else {
			timeSinceDeath += deltaTime;
		}
	}
}

void GameManager::addScore(int points)
{
	score += points;
	if (score > hiScore) {
		hiScore = score;
	}
}

void GameManager::spawnPlayer(int x, int y)
{
	ship = new Spaceship(x, y);
	canRespawn = false;
	timeSinceDeath = 0.0f;
}

float GameManager::getHealth()
{
	return ship->getHealth();
}

void GameManager::loseLife(int i)
{
	--playerLives;
	if (playerLives >= 0) {
		canRespawn = true;
	}
}

void GameManager::addLife(int i)
{
	++playerLives;
}
