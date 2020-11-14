// Xenon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "Engine.h"

int main(int argc, char* argv[])
{
    Engine engine;
    engine.init("Xenon Clone!", 640, 480);
    engine.start();
    

    return 0;
}


/*#include <iostream>
#include "GameEngine.h"

int main()
{
    GameEngine engine;
    engine.init("Xenon Clone!", 640,480);
    engine.start();
}*/