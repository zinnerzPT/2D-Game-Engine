#pragma once
class GameManager
{
private:

	GameManager() {};

public:

	static GameManager* getInstance();

	~GameManager();

private:

	static GameManager* instance;
	int score = 0;
	int hiScore = 5000;

	int playerLives = 4;

	class Spaceship* ship;

public:

	void addScore(int points);
	int getScore() { return score; };
	int getHiScore() { return hiScore; };

	void spawnPlayer(int x, int y);
	float getHealth();
	int getLives() { return playerLives; };

	void loseLife(int i = 1);
	void addLife(int i = 1);

	/*
public:

	void init(std::string windowTitle, int windowWidth, int windowHeight);
	void start();

	//void HandleEvents();

	static class Level* getLevel() { return level; };
private:
	bool isRunning;
	class SDLWrapper* sdl = nullptr;
	class Window* window = nullptr;
	static class Level* level;

public:
	static class Renderer* renderer;

	*/
};



/*



*/