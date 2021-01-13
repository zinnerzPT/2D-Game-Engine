#pragma once

#include <vector>

//Categories used for collision filtering
static const uint16_t CATEGORY_0 = 0x0001; // The default collision category
static const uint16_t CATEGORY_1 = 0x0002; // The Player collision category
static const uint16_t CATEGORY_2 = 0x0004; // The Enemy collision category
static const uint16_t CATEGORY_3 = 0x0008; // The Missile collision category
static const uint16_t CATEGORY_4 = 0x0010; // The Enemy Projectile collision category
static const uint16_t CATEGORY_5 = 0x0020; // The Power Up collision category
static const uint16_t CATEGORY_6 = 0x0040; // The Companion collision category
static const uint16_t CATEGORY_7 = 0x0080;
static const uint16_t CATEGORY_8 = 0x0100;
static const uint16_t CATEGORY_9 = 0x0200;
static const uint16_t CATEGORY_10 = 0x0400;
static const uint16_t CATEGORY_11 = 0x0800;
static const uint16_t CATEGORY_12 = 0x1000;
static const uint16_t CATEGORY_13 = 0x2000;
static const uint16_t CATEGORY_14 = 0x4000;
static const uint16_t CATEGORY_15 = 0x8000;


class RigidBody
{
public:
	RigidBody();

	void makeDynamic(float density);
	void createBody(float position[2], float halfSize[2]);

	void setPosition(float position[2]);
	void setTransform(float position[2], float angle);
	void setVelocity(float linearVelocity[2]);
	void setEnabled(bool value);
	void setCollisionFilter(uint16_t categoryBits, uint16_t maskBits);

	float* getPosition();
	class b2Body* getBody();
	struct b2BodyDef* getBodyDef();
	struct b2FixtureDef* getFixtureDef();

	~RigidBody();

private:
	bool isDynamic = false;

	float bodyDensity = 0.0f;
	float position[2]{ 0.0f, 0.0f };
	class b2Body* body;
	class b2Fixture* fixture;
	struct b2BodyDef* bodyDef;
	struct b2FixtureDef* fixtureDef;
};