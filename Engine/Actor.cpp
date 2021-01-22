#include "Actor.h"
#include "Engine.h"
#include "Level.h"
#include "Renderer.h"
#include "SceneViewer.h"
#include <glm/glm.hpp>

#define SIDE_STEPS 3

static float vertices[4][5] = {
	{ 0.0f, 0.0f, 0.0f, 0.0f, 1.0f},
	{ 1.0f, 0.0f, 0.0f, 1.0f / (2.0f * SIDE_STEPS + 1), 1.0f},
	{ 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
	{ 1.0f, 1.0f, 0.0f, 1.0f / (2.0f * SIDE_STEPS + 1), 0.0f}
};

Actor::Actor()
{
	Engine::getLevel()->addActor(this);
}

void Actor::render()
{
	for (Texture* t : textures)
	{
		//SDL way
		Engine::renderer->copy(t, t->getSrcRect(), t->getDstRect(), flipHorizontal,flipVertical);
	}
}

void Actor::draw(class SceneViewer* v /*= nullptr*/)
{
	for (Texture* t : textures)
	{
		//glm::vec2 offset = glm::vec2((SIDE_STEPS) / (SIDE_STEPS * 2.0f + 1), 0.0f);
		glBindVertexArray(t->getVAO());
		v->setTexture(t->getTextureID(), t->getOffsetX(), t->getOffsetY()); //&glm::vec2((direction + SIDE_STEPS) / (SIDE_STEPS * 2.0f + 1), 0.0f));
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
