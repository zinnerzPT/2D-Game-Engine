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
	for (Texture* t : textures)
	{
		Engine::renderer->copy(t, t->getSrcRect(), t->getDstRect());
	}
}

Actor::~Actor()
{
	Engine::getLevel()->addActorToRemove(this);
}
