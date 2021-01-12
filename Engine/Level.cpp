#include "Level.h"

#include <glm/ext.hpp>
#include "ContactListener.h"
#include "SceneViewer.h"

Level::Level()
{
	gravity = new b2Vec2(0.0f, 0.0f);
	world = new b2World(*gravity);

	ContactListener* contactListener = new ContactListener();
	world->SetContactListener(contactListener);
}

void Level::addActor(Actor* actor)
{
	this->actorsToAdd.push_back(actor);
}

void Level::addAnimation(Animation* animation)
{
	this->animationsToAdd.push_back(animation);
}

// Box2D
void Level::addBodyToEnable(class b2Body* b)
{
	this->bodiesToEnable.push_back(b);
}

void Level::addBodyToDisable(class b2Body* b)
{
	this->bodiesToDisable.push_back(b);
}


void Level::addActorToRemove(Actor* actor)
{
	this->actorsToRemove.push_back(actor);
}

void Level::addAnimationToRemove(Animation* animation)
{
	this->animationsToRemove.push_back(animation);
}

void Level::update(float deltaTime)
{
	//update actors
	for (Actor* a : actors) {
		a->update(deltaTime);
	}
}

void Level::render(SceneViewer* viewer)
{
	for (Actor* a : actors) {
		//viewer->setModelMatrix(a->transform);
		a->render(viewer);
	}
}

void Level::animate()
{
	for (Animation* an : animations) {
		an->update();
	}
}

void Level::updateBodies()
{
	// Enable bodies
	for (b2Body* b : bodiesToEnable)
	{
		b->SetEnabled(true);
	}
	bodiesToEnable.clear();

	// Disable bodies
	for (b2Body* b : bodiesToDisable)
	{
		b->SetEnabled(false);
	}
	bodiesToDisable.clear();
}

void Level::updateActors()
{
	for (Actor* a : actorsToRemove)
	{
		this->actors.erase(std::remove(this->actors.begin(), this->actors.end(), a), this->actors.end());
		delete a;
	}
	actorsToRemove.clear();

	for (Actor* a : actorsToAdd)
	{
		this->actors.push_back(a);
	}
	actorsToAdd.clear();
}

void Level::updateAnimations()
{
	for (Animation* an : animationsToRemove)
	{
		this->animations.erase(std::remove(this->animations.begin(), this->animations.end(), an), this->animations.end());
	}
	animationsToRemove.clear();

	for (Animation* an : animationsToAdd)
	{
		this->animations.push_back(an);
	}
	animationsToAdd.clear();
}

Level::~Level()
{
	for (Actor* a : actors) {
		delete(a);
	}
	delete gravity;
	delete world;
}
