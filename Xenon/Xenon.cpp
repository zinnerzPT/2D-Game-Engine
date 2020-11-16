// Xenon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"
#include "Spaceship.h"
#include "Enemy.h"

int main(int argc, char* argv[])
{
    Engine engine;
    engine.init("Xenon Clone!", 640, 480);

    Enemy* enemy = new Enemy();

    engine.start();

    return 0;
}