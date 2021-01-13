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
		Engine::renderer->copy(t, t->getSrcRect(), t->getDstRect(), flipHorizontal,flipVertical);
	}
}

void Actor::destroy()
{
	Engine::getLevel()->addActorToRemove(this);
}

Actor::~Actor()
{

}
