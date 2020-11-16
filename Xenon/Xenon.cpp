// Xenon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"
#include "Level.h"
#include "Spaceship.h"
#include "Background.h"
#include "Enemy.h"

int main(int argc, char* argv[])
{
    Engine engine;
    engine.init("Xenon Clone!", 640, 480);

    Background* background = new Background();
    Spaceship* ship = new Spaceship(200, 200);
    //Enemy* enemy = new Enemy();

    //engine.getLevel()->addActor(background);
    //engine.getLevel()->addActor(ship);

    engine.start();

    //delete background;
    //delete ship;

    return 0;
}