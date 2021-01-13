// Xenon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"
#include "Level.h"
#include "Spaceship.h"
#include "Background.h"
#include "ScrollingBackground.h"
#include "Loner.h"
#include "Rusher.h"
#include "Enemy.h"
#include "Missile.h"
#include "Rusher.h"
#include "Scoreboard.h"
#include "ShieldPowerUp.h"
#include "WeaponPowerUp.h"
#include "CompanionPowerUp.h"

int main(int argc, char* argv[])
{
	Engine* engine = Engine::getInstance();

	engine->init("Xenon Clone!", 640, 480);

	// Background
	Background* background = new Background("../graphics/galaxy2.bmp");
	int offset = -512;
	for (int i = 0; i < 8; ++i)
	{
		ScrollingBackground* scrollingBackground = new ScrollingBackground("../graphics/Blocks.bmp", 64, 1408, 224, 128, 0, 0, 224, 128, 416 + 20, offset);
		offset += 128;
	}
	offset = -512;
	for (int i = 0; i < 8; ++i)
	{
		ScrollingBackground* scrollingBackground = new ScrollingBackground("../graphics/Blocks.bmp", 288, 1344, 64, 192, 0, 0, 64, 192, -1, offset);
		offset += 128;
	}
	offset = -320;
	{
		ScrollingBackground* topLayerRight0 = new ScrollingBackground("../graphics/Blocks.bmp", 160, 352, 160, 32, 0, 0, 160, 32, 480, offset, false, false, 2.5f, 1024);
		offset += 32;
		ScrollingBackground* topLayerRight1 = new ScrollingBackground("../graphics/Blocks.bmp", 256, 96, 192, 64, 0, 0, 192, 64, 448, offset, false, false, 2.5f, 1024);
		offset += 64;
		ScrollingBackground* topLayerRight2 = new ScrollingBackground("../graphics/Blocks.bmp", 224, 160, 224, 160, 0, 0, 224, 160, 416, offset, false, false, 2.5f, 1024);
		offset += 160;
		ScrollingBackground* topLayerRight3 = new ScrollingBackground("../graphics/Blocks.bmp", 160, 320, 160, 32, 0, 0, 160, 32, 480, offset, false, false, 2.5f, 1024);
	}
	// Power ups
	ShieldPowerUp* shieldPU = new ShieldPowerUp(50, 100);
	WeaponPowerUp* weaponPU = new WeaponPowerUp(100, 200);
	WeaponPowerUp* weaponPU2 = new WeaponPowerUp(50, 200);
	CompanionPowerUp* companionPU = new CompanionPowerUp(100, 300);
	CompanionPowerUp* companionPU2 = new CompanionPowerUp(50, 300);
	// Player
	Spaceship* ship = new Spaceship(304, 400);
	// Enemies
	Loner* loner = new Loner(200, 180);
	Rusher* rusher = new Rusher(400, -40);
	// UI
	Scoreboard* scoreboard = new Scoreboard(200, 200);

	engine->start();

	delete engine;
	return 0;
}