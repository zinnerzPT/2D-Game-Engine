#include "Level.h"

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

Level::~Level()
{
	for (Actor* a : actors) {
		delete(a);
	}
}
