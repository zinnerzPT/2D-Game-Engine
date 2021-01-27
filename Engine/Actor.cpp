#include "Actor.h"
#include "Engine.h"
#include "Level.h"
#include "Renderer.h"
#include "SceneViewer.h"
#include <glm/glm.hpp>
#include "Transform.h"

Actor::Actor(int x,int y)
{
	Engine::getLevel()->addActor(this);
	transform = new Transform();
	transform->Translate(x, y);
}

void Actor::render()
{
	transform->setPosition(xpos, ypos);
	for (Texture* t : textures)
	{
		//SDL way
		Engine::renderer->copy(t, t->getSrcRect(), t->getDstRect(), flipHorizontal, flipVertical);
	}
}

void Actor::draw(class SceneViewer* v /*= nullptr*/)
{
	for (Texture* t : textures)
	{
		t->draw(v);
	}
}

void Actor::destroy()
{
	Engine::getLevel()->addActorToRemove(this);
}

Actor::~Actor()
{
	for (Texture* t : textures)
	{
		delete t;
	}
	for (Tilemap* tm : tilemaps)
	{
		delete tm;
	}
	for (Animation* an : animations)
	{
		delete an;
	}
}
