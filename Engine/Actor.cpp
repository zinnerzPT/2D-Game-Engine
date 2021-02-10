#include "Actor.h"
#include "Engine.h"
#include "Level.h"
#include "SceneViewer.h"
#include <glm/glm.hpp>
#include "Transform.h"

// FOR DEBUG PURPOSES ONLY
#include <iostream>

Actor::Actor(int x,int y)
{
	if (x && y) {
		xpos = x;
		ypos = y;
	}
	Engine::getLevel()->addActor(this);
	transform = new Transform();
	transform->Translate(x, y, layer);
}

void Actor::draw(class SceneViewer* v /*= nullptr*/)
{
	transform->setPosition(xpos, ypos, layer);
	for (Texture* t : textures)
	{
		if (t->getPosOffsetX() || t->getPosOffsetY())
		{
			t->draw(v, transform);
		}
		else
		{
			t->draw(v);
		}
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
