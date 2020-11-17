#include "Actor.h"
#include "Engine.h"
#include "Level.h"
#include "Renderer.h"

Actor::Actor()
{
	Engine::getLevel()->addActor(this);
}

void Actor::render() 
{
	Engine::renderer->copy(texture, texture->getSrcRect(), texture->getDstRect());
}