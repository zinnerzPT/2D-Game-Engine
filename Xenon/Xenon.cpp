// Xenon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"
#include "Level.h"
#include "Spaceship.h"
#include "Background.h"
#include "Loner.h"
#include "Rusher.h"
#include "Enemy.h"

int main(int argc, char* argv[])
{
    Engine engine;
    engine.init("Xenon Clone!", 640, 480);

    Background* background = new Background();
    Spaceship* ship = new Spaceship(304, 400);
    Loner* loner = new Loner(200, 0);
    //Enemy* enemy = new Enemy();

    engine.start();

    return 0;
}