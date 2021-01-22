#include "Actor.h"
#include "Engine.h"
#include "Level.h"
#include "Renderer.h"
#include "SceneViewer.h"
#include <glm/glm.hpp>

Actor::Actor()
{
	Engine::getLevel()->addActor(this);
}

void Actor::render()
{
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
		glBindVertexArray(t->getVAO());
		v->setTexture(t->getTextureID(), t->getOffsetX(), t->getOffsetY());
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
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
