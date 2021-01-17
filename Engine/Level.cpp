#include "Level.h"
#include "ContactListener.h"

#include "OpenALWrapper.h"

Level::Level(float gravityX, float gravityY)
{
	// Create a world to run the physics
	b2Vec2 gravity = b2Vec2(gravityX, gravityY);
	world = new b2World(gravity);
	ContactListener* contactListener = new ContactListener();
	world->SetContactListener(contactListener);

	// Initialize audio
	alWrapper = OpenALWrapper::getInstance();
	device = alWrapper->openDefaultAudioDevice();
	context = alWrapper->createAudioContext(device);
	alWrapper->createAudioListener();
}

void Level::addActor(Actor* actor)
{
	this->actorsToAdd.push_back(actor);
}

void Level::addAnimation(Animation* animation)
{
	this->animationsToAdd.push_back(animation);
}

void Level::addCanvas(UICanvas* canvas)
{
	this->canvasesToAdd.push_back(canvas);
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
	// Check if the actor is already going to be removed
	for (Actor* a : actorsToRemove)
	{
		if (a == actor)
		{
			return;
		}
	}
	this->actorsToRemove.push_back(actor);
}

void Level::addAnimationToRemove(Animation* animation)
{
	// Check if the animation is already going to be removed
	for (Animation* an : animationsToRemove)
	{
		if (an == animation)
		{
			return;
		}
	}
	this->animationsToRemove.push_back(animation);
}

void Level::addCanvasToRemove(UICanvas* canvas)
{
	// Check if the canvas is already going to be removed
	for (UICanvas* c : canvasesToRemove)
	{
		if (c == canvas)
		{
			return;
		}
	}
	this->canvasesToRemove.push_back(canvas);
}

void Level::update(float deltaTime)
{
	//update actors
	for (Actor* a : actors) {
		a->update(deltaTime);
	}
	for (UICanvas* c : canvases) {
		c->update(deltaTime);
	}
}

void Level::render()
{
	for (Actor* a : actors) {
		a->render();
	}
	for (UICanvas* c : canvases) {
		c->render();
	}
}

void Level::animate()
{
	for (Animation* an : animations) {
		an->update();
	}
}

struct Sound* Level::loadSoundFile(const char* filepath)
{
	return alWrapper->loadSoundFromFile(filepath);
}

void Level::playSound(struct Sound* sound)
{
	alWrapper->playSound(sound);
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

void Level::updateCanvases()
{
	for (UICanvas* c : canvasesToRemove)
	{
		this->canvases.erase(std::remove(this->canvases.begin(), this->canvases.end(), c), this->canvases.end());
		delete c;
	}
	canvasesToRemove.clear();

	for (UICanvas* c : canvasesToAdd)
	{
		this->canvases.push_back(c);
	}
	canvasesToAdd.clear();
}

Level::~Level()
{
	for (Actor* a : actors) 
	{
		addActorToRemove(a);
	}
	updateActors();

	delete world;

	alWrapper->destroyAudioContext(context);
	alWrapper->closeAudioDevice(device);
}
