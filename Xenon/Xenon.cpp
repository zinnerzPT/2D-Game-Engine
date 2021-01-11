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

	Background* background = new Background();
	Spaceship* ship = new Spaceship(304, 400);
	Loner* loner = new Loner(200, 32);
	Rusher* rusher = new Rusher(400, 450);
	Scoreboard* scoreboard = new Scoreboard(200, 200);

	engine->start();

	delete engine;

	return 0;
}