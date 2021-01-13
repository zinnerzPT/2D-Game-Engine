#include "GameManager.h"
#include "Spaceship.h"

GameManager* GameManager::instance = nullptr;

GameManager* GameManager::getInstance()
{
	if (instance == nullptr) {
		instance = new GameManager();
	}
	return instance;
}

GameManager::~GameManager()
{
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
}

float GameManager::getHealth()
{
	return ship->getHealth();
}

void GameManager::loseLife(int i)
{
	--playerLives;
	if (playerLives >= 0) {
		spawnPlayer(304, 400);
	}
}

void GameManager::addLife(int i)
{
	++playerLives;
}
