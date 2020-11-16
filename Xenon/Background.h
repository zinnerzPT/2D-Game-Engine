#pragma once
#include "Actor.h"
class Background :
    public Actor
{
public:
    Background();
    void update(float deltaTime);
};

