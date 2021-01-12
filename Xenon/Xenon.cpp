// Xenon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"
#include "Level.h"
#include "Spaceship.h"
#include "Background.h"
#include "Loner.h"
#include "Rusher.h"
#include "Enemy.h"
#include "Missile.h"
#include "Rusher.h"
#include "Scoreboard.h"

int main(int argc, char* argv[])
{
	Engine* engine = Engine::getInstance();

	engine->init("Xenon Clone!", 640, 480);

	Background* background = new Background("../graphics/galaxy2.bmp");
	int offset = -512;
	for (int i = 0; i < 9; ++i)
	{
		Background* scrollingBackground = new Background("../graphics/Blocks.bmp", 64, 1408, 224, 128, 0, 0, 224, 128, 416, offset);
		offset += 128;
	}
	Spaceship* ship = new Spaceship(304, 400);
	Loner* loner = new Loner(200, 180);
	Rusher* rusher = new Rusher(400, -40);
	Scoreboard* scoreboard = new Scoreboard(200, 200);

	engine->start();

	delete engine;

	return 0;
}