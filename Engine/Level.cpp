#include "Level.h"

#include "ContactListener.h"

Level::Level()
{
	gravity = new b2Vec2(0.0f, 0.0f);
	world = new b2World(*gravity);

	ContactListener* contactListener = new ContactListener();
	world->SetContactListener(contactListener);
}

void Level::add(Actor* actor)
{
	this->actors.push_back(actor);
	//actor.setLevel(this);
}

void Level::update(float deltaTime)
{
	for (Actor* a : actors) {
		a->update(deltaTime);
	}
	//actors to remove

	//actors to remove.clear

	//actors to add

	//actors to add.clear
}

class b2World* Level::getWorld()
{
	return world;
}

Level::~Level()
{
	for (Actor* a : actors) {
		delete(a);
	}
	delete gravity;
	delete world;
}
