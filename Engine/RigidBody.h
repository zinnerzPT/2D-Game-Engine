#pragma once

#include <vector>

class RigidBody
{
public:
	RigidBody();

	void makeDynamic(float density);

	void createBody(float position[2], float halfSize[2]);

	float* getPosition();

	class b2Body* getBody();
	class b2BodyDef* getBodyDef();
	class b2FixtureDef* getFixtureDef();

	~RigidBody();

private:
	bool isDynamic = false;

	float bodyDensity = 0.0f;

	class b2Body* body;
	class b2BodyDef* bodyDef;
	class b2FixtureDef* fixtureDef;
};