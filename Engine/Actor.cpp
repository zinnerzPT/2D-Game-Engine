#include "Actor.h"
#include <iostream>
#include "Engine.h"
#include "Level.h"

Actor::Actor()
{
	Engine::getLevel()->add(this);
}
