// Xenon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"
#include "Spaceship.h"

int main(int argc, char* argv[])
{
    Engine engine;
    engine.init("Xenon Clone!", 640, 480);
    engine.start();

    return 0;
}