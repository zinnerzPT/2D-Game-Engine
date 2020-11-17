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

int main(int argc, char* argv[])
{
    Engine engine;
    engine.init("Xenon Clone!", 640, 480);

    Background* background = new Background();
    Spaceship* ship = new Spaceship(304, 400);
    Loner* loner = new Loner(200, 0);

	float position[2]{ 200.0f, 250.0f };
	float halfSize[2]{ 4.0f, 4.0f };
	float velocity[2]{ 0.0f, -80.0f };
	Missile* missile = new Missile(position, halfSize, 1.0f, velocity);

    engine.start();

    return 0;
}