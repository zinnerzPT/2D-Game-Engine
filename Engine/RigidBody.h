#pragma once

#include <vector>

class RigidBody
{
public:
	RigidBody();

	void makeDynamic(float density);

	void createBody(float position[2], float halfSize[2]);

	void setVelocity(float linearVelocity[2]);

	float* getPosition();
	class b2Body* getBody();
	struct b2BodyDef* getBodyDef();
	struct b2FixtureDef* getFixtureDef();

	~RigidBody();

private:
	bool isDynamic = false;

	float bodyDensity = 0.0f;

	class b2Body* body;
	struct b2BodyDef* bodyDef;
	struct b2FixtureDef* fixtureDef;
};