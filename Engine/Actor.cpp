#include "Actor.h"
#include <iostream>
#include "Engine.h"
#include "Level.h"
#include "Renderer.h"

Actor::Actor()
{
	Engine::getLevel()->add(this);
}

void Actor::render() 
{
	Engine::renderer->copy(texture, &srcRect, &destRect);
}